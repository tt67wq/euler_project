defmodule PandigitalFibonacciEnds do
  @moduledoc """
  https://projecteuler.net/problem=104
  """
  @base 1000000000
  @all_digit [1, 2, 3, 4, 5, 6, 7, 8, 9]

  require Logger

  def digits_add(list1, list2), do: da(list1 |> Enum.reverse, list2 |> Enum.reverse, 0, [])
  defp da([], [], 0, acc), do: acc
  defp da([], [], m, acc), do: [m | acc]
  defp da(list, [], m, acc), do: da(list, [0], m, acc)
  defp da([], list, m, acc), do: da([0], list, m, acc)
  defp da([h1|t1], [h2|t2], m, acc) do
    h = h1 + h2 + m
    cond do
      h > 9 -> da(t1, t2, div(h, 10), [rem(h, 10)|acc])
      :else -> da(t1, t2, 0, [h|acc])
    end
  end

  def solution(), do: sl([1], [1], 2)
  defp sl(a, b, index) do
    cond do
      b |> Enum.reverse |> Enum.take(9) |> Enum.sort() == @all_digit and b |> Enum.take(9) |> Enum.sort() == @all_digit -> index
      :else -> sl(b, digits_add(a, b), index+1)
    end
  end
end
