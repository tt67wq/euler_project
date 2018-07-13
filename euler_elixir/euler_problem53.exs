defmodule CombinatoricSelections do
  @moduledoc """
  There are exactly ten ways of selecting three from five, 12345:

  123, 124, 125, 134, 135, 145, 234, 235, 245, and 345

  In combinatorics, we use the notation, 5C3 = 10.

  In general,

  nCr =	
  n!
  r!(n−r)!
  ,where r ≤ n, n! = n×(n−1)×...×3×2×1, and 0! = 1.
  It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.

  How many, not necessarily distinct, values of  nCr, for 1 ≤ n ≤ 100, are greater than one-million?
  """

  @doc """
  幂
  """
  @spec power(Integer) :: Integer
  def power(0), do: 1
  def power(x), do: power(x, 1)
  defp power(0, acc), do: acc
  defp power(index, acc), do: power(index-1, acc * index)

  @doc """
  计算组合数量
  """
  @spec choose(Integer, Integer) :: Integer
  def choose(n, r), do: n-r+1..n |> Enum.reduce(1, fn x, acc -> acc * x end) |> div(power(r))

  def solution(), do: s(1, 0)
  defp s(101, acc), do: acc
  defp s(index, acc) do
    nacc = 1..index |> Enum.map(fn x -> choose(index, x) end) |> Enum.filter(fn x -> x > 1000000 end) |> length()
    s(index + 1, nacc + acc)
  end
end
