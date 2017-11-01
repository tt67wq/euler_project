defmodule SingularIntegerRightTriangles do
  @moduledoc """
  https://projecteuler.net/problem=75

  思路:
  根据维基百科，勾股数可表示为
  a = k(m2 - n2)
  b = 2kmn
  c = k(m2 + n2)

  周长为 2km(m + n)
  """
  @doc """
  求最大公约数
  """
  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  def get_list(m, n, limit), do: gl(2 * m * (m + n), 2 * m * (m + n), limit, [])
  defp gl(t, l, limit, acc) do
    cond do
      t < limit -> gl(t + l, l, limit, [t | acc])
      :else -> acc
    end
  end


  def solution(limit), do: sl(limit, 2, 1, %{})
  defp sl(limit, m, _, state) when 2 * m * m >= limit do
    state |> Map.values()
    |> Enum.filter(fn x -> x == 1 end)
    |> length()
  end
  defp sl(limit, m, n, state) when n >= m, do: sl(limit, m + 1, 1, state)
  defp sl(limit, m, n, state) do
    cond do
      rem(m + n, 2) == 0 -> sl(limit, m, n + 1, state)
      :else ->
  	cond do
  	  gcd(m, n) != 1 -> sl(limit, m, n + 1, state)
  	  :else ->
  	    sl(limit, m, n + 1, update_state(limit, m, n, state))
  	end
    end
  end

  def update_state(limit, m, n, state) do
    get_list(m, n, limit)
    |> Enum.reduce(state, fn x, acc -> Map.update(acc, x, 1, fn x -> x + 1 end) end)
  end
end
