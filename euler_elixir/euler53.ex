defmodule Euler53 do
  @moduledoc """
  http://pe-cn.github.io/53/
  """

  def pascal(), do: pascal_gene(%{0 => [1], 1 => [1, 1]}, 1)

  defp pascal_gene(state, 100), do: state

  defp pascal_gene(state, level) do
    nums = Map.get(state, level)

    Map.put(state, level + 1, level_iter(nums, []))
    |> pascal_gene(level + 1)
  end

  defp level_iter([h1, h2], acc), do: [1 | Enum.reverse([1, h1 + h2 | acc])]
  defp level_iter([h1, h2 | t], acc), do: level_iter([h2 | t], [h1 + h2 | acc])

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      pascal()
      |> Map.to_list()
      |> Enum.map(fn {_, x} -> Enum.filter(x, fn y -> y > 1_000_000 end) end)
      |> Enum.map(fn x -> Enum.count(x) end)
      |> Enum.sum()

    timeuse = now() - start
    IO.inspect(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
