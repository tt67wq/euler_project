defmodule PandigitalPrime do
  @moduledoc """
  We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once.
  For example, 2143 is a 4-digit pandigital and is also prime.
  What is the largest n-digit pandigital prime that exists?
  """

  @doc """
  获得一个数字所有位数组成的集合
  ## Example

      iex> PandigitalPrime.number2set(12345)
      #MapSet<[1, 2, 3, 4, 5]>
  """
  @spec number2set(Integer) :: MapSet
  def number2set(n), do: number2set(n, MapSet.new())
  defp number2set(0, acc), do: acc
  defp number2set(n, acc), do: number2set(div(n, 10), MapSet.put(acc, rem(n, 10)))

  @doc """
  判断一个数字是否是pandigital的

  ## Example
  
      iex> PandigitalPrime.isPandigital(1234)
      true
  """
  @spec isPandigital(Integer) :: boolean
  def isPandigital(n), do: MapSet.equal?(1..length(Integer.to_charlist(n)) |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end), number2set(n))


  @spec prime?(Integer) :: boolean
  def prime?(1), do: false
  def prime?(x), do: prime(x, 2, [])
  defp prime(x, y, acc) when y * y > x, do: length(acc) == 0
  defp prime(_x, _y, acc) when length(acc) > 0, do: false
  defp prime(x, y, acc) do
    cond do
      rem(x, y) == 0 -> prime(x, y+1, [y|acc])
      true -> prime(x, y+1, acc)
    end
  end

  def largestPandigitalPrime(), do:  1234567..7654321 |> Enum.filter(fn x -> prime?(x) end) |> Enum.filter(fn x -> isPandigital(x) end)
end
