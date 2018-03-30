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
  """
  def extend_gcd(a, b), do: eg(a, b, {0, 1}, {1, 0})
  defp eg(a, 0, {_, lx}, {_, ly}), do: {lx, ly, a}

  defp eg(a, b, {x, lx}, {y, ly}) do
    quotient = div(a, b)
    eg(b, rem(a, b), {lx - quotient * x, x}, {ly - quotient * y, y})
  end
end
