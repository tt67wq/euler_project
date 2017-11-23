defmodule DigitPowerSum do
  @moduledoc """
  https://projecteuler.net/problem=119
  """
  require Logger
  @limit 100000000000000000000

  def int2list(num), do: i2l(num, [])
  defp i2l(0, acc), do: acc
  defp i2l(num, acc), do: i2l(num |> div(10), [num |> rem(10)|acc])

  def satisfy?(num) do
    ds = int2list(num) |> Enum.sum()
    l = rem(ds, 10)
    case l do
      0 ->
	cond do
	  rem(num, 10) == 0 -> s?(ds, ds, num)
	  :else -> false
	end
      1 ->
	cond do
	  rem(num, 10) == 1 -> s?(ds, ds, num)
	  :else -> false
	end
      2 ->
	cond do
	  Enum.member?([2,4,6,8], rem(num, 10)) -> s?(ds, ds, num)
	  :else -> false
	end
      3 ->
	cond do
	  Enum.member?([3,9,7,1], rem(num, 10)) -> s?(ds, ds, num)
	  :else -> false
	end
      4 ->
	cond do
	  Enum.member?([4,6], rem(num, 10)) -> s?(ds, ds, num)
	  :else -> false
	end
      5 ->
	cond do
	  rem(num, 10) == 5 -> s?(ds, ds, num)
	  :else -> false
	end
      6 ->
	cond do
	  rem(num, 10) == 6 -> s?(ds, ds, num)
	  :else -> false
	end
      7 ->
	cond do
	  Enum.member?([3,9,7,1], rem(num, 10)) -> s?(ds, ds, num)
	  :else -> false
	end
      8 ->
	cond do
	  Enum.member?([2,4,6,8], rem(num, 10)) -> s?(ds, ds, num)
	  :else -> false
	end
      9 ->
	cond do
	  Enum.member?([9,1], rem(num, 10)) -> s?(ds, ds, num)
	  :else -> false
	end
    end
  end
  defp s?(_ds, acc, num) when acc > num, do: false
  defp s?(_ds, acc, num) when acc == num, do: true
  defp s?(ds, acc, num), do: s?(ds, acc * ds, num)


  def generate_cands(), do: gc(2, 4, [])
  defp gc(index, _, acc) when index > 100, do: acc |> Enum.sort() |> Enum.dedup
  defp gc(index, bcc, acc) when bcc > @limit, do: gc(index+1, (index+1) * (index+1), acc)
  defp gc(index, bcc, acc), do: gc(index, bcc * index, [bcc|acc])

  def solution() do
    nums = generate_cands()
    sl(nums, 1)
  end
  defp sl([], index), do: index
  defp sl([h|t], index) do
    cond do
      h < 10 -> sl(t, index)
      satisfy?(h) ->
	Logger.info("#{index}, #{h}")
	sl(t, index+1)
      :else -> sl(t, index)
    end
  end
end
