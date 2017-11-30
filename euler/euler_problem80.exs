defmodule SquareRootDigitalExpansion do
  @moduledoc """
  https://projecteuler.net/problem=80
  """
  require Logger
  @doc """
  整数开方至指定精度, 利用长除法
  https://zh.wikipedia.org/wiki/%E5%B9%B3%E6%96%B9%E6%A0%B9#.E9.95.B7.E9.99.A4.E5.BC.8F.E7.AE.97.E6.B3.95
  ## Example

      iex> long_div_root(200, 100)
      1414213562373095048801688724209698078569671875376948073176679737990732478462107038850387534327641572
  """
  def long_div_root(num, sd) do
    [h|t] = int_slice(num)
    a = nearest_root(h)
    cond do
      length(t) > 0 ->
	[h1|_] = t
	d = (h - a * a) * 100 + h1
	ldr(d, t, sd, 1, a)
      :else ->
	d = (h - a * a) * 100
	ldr(d, [], sd, 1, a)
    end
  end

  defp ldr(_d, _list, sd, index, a) when sd == index, do: a
  defp ldr(d, [], sd, index, a) do
    b = get_b(a, d)
    # Logger.info("a: #{a}, d: #{d}, b: #{b}")
    ldr((d - (20 * a + b) * b) * 100, [], sd, index + 1, a * 10 + b)    
  end
  defp ldr(d, [h|t], sd, index, a) do
    b = get_b(a, d)
    # Logger.info("a: #{a}, d: #{d}, b: #{b}")
    ldr((d - (20 * a + b) * b) * 100 + h, t, sd, index + 1, a * 10 + b)
  end

  def get_b(a, d), do: gb(a, d, 1, 20 * a + 1)
  defp gb(a, d, index, acc) when acc < d, do: gb(a, d, index + 1, (20 * a + index+1) * (index + 1))
  defp gb(_a, _d, index, _acc), do: index - 1


  def get_digit_sum(num), do: gds(num, 0)
  defp gds(0, acc), do: acc
  defp gds(num, acc), do: gds(div(num, 10), acc + rem(num, 10))

  @doc """
  寻找不大于num平方根的最大整数
  ## Example

      iex> nearest_root(40)
      6

  """
  def nearest_root(num), do: nr(num, 1)
  defp nr(num, acc) when acc * acc > num, do: acc - 1
  defp nr(num, acc), do: nr(num, acc + 1)

  @doc """
  整数从右向左两两分割
  ## Example

      iex> int_slice(21154)
      [2, 11, 54]

  """
  def int_slice(num), do: is(num, [])
  defp is(0, acc), do: acc
  defp is(num, acc), do: is(div(num, 100), [rem(num, 100)|acc])

  def root_digit_sum(num) do
    v = long_div_root(num, 100) |> get_digit_sum()
    Logger.info("digit sum root of #{num} is #{v}")
    v
  end

  def solution() do
    2..99 |> Enum.filter(fn x -> not Enum.member?([4, 9, 16, 25, 36, 49, 64, 81], x) end)
    |> Enum.reduce(0, fn x, acc -> root_digit_sum(x) + acc end)
  end


end
