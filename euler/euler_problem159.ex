defmodule Euler159 do
  @moduledoc """
  https://projecteuler.net/problem=159
  """
  require Logger

  @limit 1_000_000

  @spec digital_root(Integer) :: Integer
  def digital_root(num) when num < 10, do: num
  def digital_root(num), do: rem(num - 1, 9) + 1

  defp now(), do: :os.system_time(:milli_seconds)

  @spec iter(Integer, map()) :: map()
  def iter(base, origin_map), do: iter(base, 2, digital_root(base), base * 2, origin_map)

  defp iter(_base, _index, _dr, bcc, acc) when bcc > @limit, do: acc

  defp iter(base, index, dr, bcc, acc) do
    {a, list} = Map.fetch!(acc, bcc)
    {c, list2} = Map.fetch!(acc, index)
    b = dr + c

    cond do
      a < b ->
        iter(
          base,
          index + 1,
          dr,
          bcc + base,
          Map.update(acc, bcc, {a, list}, fn _ -> {b, [base | list2]} end)
        )

      :else ->
        iter(base, index + 1, dr, bcc + base, acc)
    end
  end

  def run() do
    start = now()

    origin_map =
      1..@limit |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, x, {digital_root(x), [1, x]}) end)

    res =
      2..div(@limit, 2)
      |> Enum.reduce(origin_map, fn x, acc -> iter(x, acc) end)
      |> Map.delete(1)
      |> Map.delete(@limit)
      |> Map.values()
      |> Enum.reduce(0, fn {x, _}, acc -> acc + x end)

    timeuse = now() - start
    IO.inspect(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
