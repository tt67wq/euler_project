defmodule Euler164 do
  @moduledoc """
  https://projecteuler.net/problem=164
  """

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    cs = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

    units =
      for a <- cs,
          b <- cs,
          c <- cs do
        [a, b, c]
      end
      |> Enum.filter(fn x -> Enum.sum(x) <= 9 end)

    mp_func = fn x, acc ->
      Map.update(acc, Enum.take(x, 2), 1, &(&1 + 1))
    end

    mp_func2 = fn x, acc ->
      Map.update(acc, Enum.take(x, 2), [x], &[x | &1])
    end

    mp_func3 = fn x, acc ->
      Map.update(acc, Enum.take(x, -2), 1, &(&1 + 1))
    end

    start_count_map = Enum.reduce(units, %{}, mp_func)
    start_unit_map = Enum.reduce(units, %{}, mp_func2)

    ends_count_map =
      Enum.filter(units, fn [a, _, _] -> a != 0 end)
      |> Enum.reduce(%{}, mp_func3)

    res =
      ends_iter(ends_count_map, start_count_map, start_unit_map, 0)
      |> Map.to_list()
      |> Enum.map(fn {unit, c} -> c * Map.get(start_count_map, unit) end)
      |> Enum.sum()

    IO.puts(res)

    timeuse = now() - start
    IO.puts("timeuse => #{timeuse} milliseconds")
  end

  defp ends_iter(ends_count_map, _, _, 16), do: ends_count_map

  defp ends_iter(ends_count_map, starts_count_map, start_unit_map, index) do
    new_ends_count_map =
      Map.to_list(ends_count_map)
      |> Enum.map(fn {unit, count} ->
        Map.get(start_unit_map, unit)
        |> Enum.reduce(%{}, fn x, acc ->
          Map.update(acc, Enum.take(x, -2), count, &(&1 + count))
        end)
      end)
      |> Enum.reduce(%{}, fn mp, acc ->
        Map.merge(acc, mp, fn _k, v1, v2 ->
          v1 + v2
        end)
      end)

    ends_iter(new_ends_count_map, starts_count_map, start_unit_map, index + 1)
  end
end
