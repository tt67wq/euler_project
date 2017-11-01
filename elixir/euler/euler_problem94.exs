defmodule AlmostEquilateralTriangles do
  @moduledoc """
  https://projecteuler.net/problem=94

  根据维基百科，勾股数可表示为
  a = k(m2 - n2)
  b = 2kmn
  c = k(m2 + n2)
  """

  @limit 1000000000
  require Logger

  @doc """
  求最大公约数
  """
  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))


  def get_triangle_set() do
    gts(2, 1, [])
  end

  defp gts(m, n, acc) when 3 * (n * n + m * m) > @limit, do: acc
  defp gts(m, n, acc) when n >= m, do: gts(m + 1, 1, acc)
  defp gts(m, n, acc) do
    cond do
      rem(m + n, 2) == 0 -> gts(m, n + 1, acc)
      :else ->
  	cond do
  	  gcd(m, n) != 1 -> gts(m, n + 1, acc)
  	  :else ->
	    a = m * m - n * n
	    b = 2 * m * n
	    c = m * m + n * n
	    gts(m, n + 1, [[a, b, c] |> Enum.sort() |acc])
  	end
    end
  end

  def almost?(a, _, c) when c == 2 * a + 1, do: true
  def almost?(a, _, c) when c == 2 * a - 1, do: true
  def almost?(a, b, c) when c == 2 * b - 1, do: true
  def almost?(a, b, c), do: false
  
  def solution() do
    get_triangle_set()
    |> Enum.filter(fn [a, b, c] -> almost?(a, b, c) end)
    |> Enum.map(fn [a, b, c] -> a * 2 + c * 2 end)
    |> Enum.filter(fn x -> x < @limit end)
    |> Enum.sum()
  end
end
