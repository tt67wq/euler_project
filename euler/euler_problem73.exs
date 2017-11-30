defmodule CountingFractions do
  @moduledoc """
  https://projecteuler.net/problem=73
  思路：
  1. 想要找到1/3和1/2之间的数量，可以从1/3向右和1/2向左逼近, 验证，不可行， 计算量太大
  2. 1/3 < x/y < 1/2 化简为 y/3 < x < y/2 可逐个y计算x数量
  """
  require Logger
  @doc """
  最大公约数
  """
  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  def count_between(n) when n < 5, do: 0
  def count_between(n) do
    l = div(n + 2, 3)
    r = div(n, 2)
    case {rem(n, 3), rem(n, 2)} do
      {0, 0} ->
	l = l + 1
	r = r - 1
	l..r |> Enum.filter(fn x -> gcd(x, n) == 1 end) |> length()
      {0, _} ->
	l = l + 1
	l..r |> Enum.filter(fn x -> gcd(x, n) == 1 end) |> length()
      {_, 0} ->
	r = r - 1
	l..r |> Enum.filter(fn x -> gcd(x, n) == 1 end) |> length()
      _ -> l..r |> Enum.filter(fn x -> gcd(x, n) == 1 end) |> length()
    end
  end

  def solution(limit) do
    start = DateTime.utc_now()
    result = sl(limit, 5, 0)
    Logger.info("result is #{result}, time use #{Time.diff(DateTime.utc_now(), start)}")
  end
  defp sl(limit, index, acc) when index > limit, do: acc
  defp sl(limit, index, acc), do: sl(limit, index + 1, acc + count_between(index))
end
