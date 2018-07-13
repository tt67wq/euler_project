defmodule ModifiedFibonacciGoldenNuggets do
  @moduledoc """
  https://projecteuler.net/problem=140
  5 ⁢x² - y² + 14 ⁢x + 1 = 0
  xn+1 = - 9 ⁢xn - 4 ⁢yn - 14 
  yn+1 = - 20 ⁢xn - 9 ⁢yn - 28
  """
  def iter(x, y), do: {-9 * x - 4 * y - 14, -20 * x - 9 * y - 28}

  def solution() do
    [{0, -1}, {0, 1}, {-3, -2}, {-3, 2}, {-4, 5}, {-4, -5}, {2, -7}, {2, 7}]
    |> Enum.reduce([], fn {x, y}, acc -> sl(1, {x, y}, [{x, y}]) ++ acc end)
    |> Enum.filter(fn {x, y} -> x > 0 and y > 0 end)
    |> Enum.map(fn {x, _} -> x end)
    |> Enum.sort()
    |> Enum.dedup()
    |> sum([], 0)
    |> Enum.sum()
  end

  defp sl(index, _, acc) when index > 10, do: acc
  defp sl(index, {x, y}, acc), do: sl(index + 1, iter(x, y), [iter(x, y) | acc])

  defp sum(_, acc, index) when index >= 30, do: acc
  defp sum([], acc, _), do: acc
  defp sum([h | t], acc, index), do: sum(t, [h | acc], index + 1)
end
