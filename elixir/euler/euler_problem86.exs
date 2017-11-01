defmodule CuboidRoute do
  @moduledoc """
  https://projecteuler.net/problem=86

  假设长方体的三条棱为 a, b, c (a > b > c)
  若最短距离为整数，则满足 a 与 b+c 能构成勾股数

  假设
  a = 2kmn
  b+c = k(m2 - n2)
  """

  require Logger

  @doc """
  求最大公约数
  """
  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  def get_num(limit), do: gn(limit, 2, 1, [])
  defp gn(limit, m, _n, acc) when 2 * m  > limit, do: acc
  defp gn(limit, m, n, acc) when n == m, do: gn(limit, m + 1, 1, acc)
  defp gn(limit, m, n, acc) do
    a = 2 * m * n
    b = m * m - n * n
    cond do
      rem(m + n, 2) == 0 -> gn(limit, m, n + 1, acc)
      gcd(m, n) != 1 -> gn(limit, m, n + 1, acc)
      a > limit and a > 2 * b -> gn(limit, m, n + 1, acc)
      b > limit and b > 2 * a -> gn(limit, m, n + 1, acc)
      a > limit and b > limit -> gn(limit, m, n + 1, acc)
      :else ->
	Logger.info("m: #{m}, n: #{n}, a: #{a}, b: #{b}")
	gn(limit, m, n+1, get_all_group(a, b, limit) ++ acc)
    end
  end

  def get_divide(a, b, k) do
    g1 = for x <- 1..div(a * k, 2),
      a * k - x <= b * k do
	[x, a * k-x, b * k] |> Enum.sort()
    end
    g2 = for y <- 1..div(b * k, 2),
      b * k - y <= a * k do
	[y, b * k - y, a * k] |> Enum.sort()
    end
    g1 ++ g2
  end
  
  def get_all_group(a, b, limit), do: gag(a, b, 1, limit, [])
  def gag(a, b, k, limit, acc) when a * k > limit and b * k > limit, do: acc |> Enum.filter(fn [_, _, x] -> x <= limit end)
  def gag(a, b, k, limit, acc), do: gag(a, b, k+1, limit, acc ++ get_divide(a, b, k))

  def solution() do
    value = get_num(1900)
    sl(value, 1899, 1000000)
  end

  defp sl(v, index, limit) do
    l = list_sub(v, index) |> length
    cond do
      l < limit -> index + 1
      :else -> sl(v, index - 1, limit)
    end
  end

  def list_sub(list1, limit), do: list1 |> Enum.filter(fn [_, _, x] -> x <= limit end)

  
end
