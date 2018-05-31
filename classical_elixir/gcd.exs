defmodule GCD do
  @moduledoc """
  求最大公约数
  """
  @doc """
  普通欧几里得算法
  """
  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  @doc """
  扩展欧几里得算法
  https://zh.wikipedia.org/wiki/%E6%89%A9%E5%B1%95%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95
  """
  def extend_gcd(a, b), do: eg(a, b, {0, 1}, {1, 0})
  defp eg(a, 0, {_, lx}, {_, ly}), do: {lx, ly, a}

  defp eg(a, b, {x, lx}, {y, ly}) do
    quotient = div(a, b)
    eg(b, rem(a, b), {lx - quotient * x, x}, {ly - quotient * y, y})
  end

  def niyuan(a, b) do
    {g, _, _} = extend_gcd(a, b)

    cond do
      g > 0 -> g
      :else -> b + g
    end
  end
end
