defmodule PalindromicSums do
  @moduledoc """
  https://projecteuler.net/problem=125
  """
  @limit 100000000

  require Logger

  def int2list(num), do: i2l(num, [])
  defp i2l(0, acc), do: acc
  defp i2l(num, acc), do: i2l(num |> div(10), [num |> rem(10)|acc])

  @doc """
  是否为回文
  """
  def palindromic?(m) do
    ls = m |> int2list()
    ls == Enum.reverse(ls)
  end

  def square_sum(list), do: list |> Enum.map(fn x -> x * x end) |> Enum.sum()
  
  def generate_consecutive_list(len, start), do: gcl(len, start, [])
  defp gcl(0, _, acc), do: acc |> Enum.reverse()
  defp gcl(len, index, acc), do: gcl(len-1, index+1, [index|acc])

  def solution() do
    sl(2, 1, []) |> MapSet.new() |> MapSet.to_list
    |> Enum.sum
  end

  defp sl(l, start, acc) do
    num = generate_consecutive_list(l, start) |> square_sum()
    cond do
      num > @limit ->
	case start do
	  1 -> acc
	  _ -> sl(l+1, 1, acc)
	end
      palindromic?(num) ->
	Logger.info(num)
	sl(l, start+1, [num|acc])
      :else -> sl(l, start+1, acc)
    end
  end  
end
