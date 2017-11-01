defmodule PermutedMultiples do
  @moduledoc """
  It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.
  Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
  """

  @doc """
  数字x乘以n之后数字组成是否不变

  ## Example

      iex> satisfy(125874, 2)
      true
  """
  @spec satisfy?(Integer, Integer) :: Integer
  def satisfy?(_x, 1), do: true
  def satisfy?(x, n) do
    a = Integer.to_charlist(x) |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end)
    b = Integer.to_charlist(x * n) |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end)
    MapSet.equal?(a, b)
  end

  def solution(), do: s(1, 2)
  defp s(index, 7), do: index
  defp s(index, count) do
    case satisfy?(index, count) do
      true -> s(index, count+1)
      _ -> s(index+1, 2)
    end
  end
end
