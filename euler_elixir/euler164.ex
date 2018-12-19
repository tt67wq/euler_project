defmodule Euler164 do
  @moduledoc """
  https://projecteuler.net/problem=164
  """

  require Logger

  # defp merge([], acc), do: acc
  # defp merge([h | t], []), do: merge(t, h)
  # defp merge([[h, _, _] | t], acc), do: merge(t, [h | acc])

  def get_unit_cluster(unit, _, 0), do: [[unit]]

  def get_unit_cluster(unit, unit_map, deep) do
    key = {unit, deep}

    case :ets.lookup(:euler164, key) do
      [{^key, v}] ->
        v

      [] ->
        res =
          get_unit_cluster(unit, unit_map, deep - 1)
          |> Enum.map(fn [x | _t] = all -> {Enum.take(x, -2), all} end)
          |> Enum.map(fn {base, all} -> {Map.get(unit_map, base), all} end)
          |> Enum.reduce([], fn {es, all}, acc -> acc ++ Enum.map(es, fn e -> [e | all] end) end)

        :ets.insert(:euler164, {key, res})
        res
    end
  end

  def start() do
    :ets.new(:euler164, [:named_table])
  end

  def run(n) do
    cs = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

    units =
      for a <- cs,
          b <- cs,
          c <- cs do
        [a, b, c]
      end
      |> Enum.filter(fn x -> Enum.sum(x) <= 9 end)

    # IO.puts(Enum.count(units))

    mp_func = fn x, acc ->
      Map.update(acc, Enum.take(x, 2), [x], &[x | &1])
    end

    unit_map = Enum.reduce(units, %{}, mp_func)

    start_units = Enum.filter(units, fn [a, _, _] -> a != 0 end)

    start_units
    |> Enum.map(fn unit -> get_unit_cluster(unit, unit_map, n) end)
    |> Enum.map(fn xs -> Enum.count(xs) end)
    |> Enum.sum()
  end
end
