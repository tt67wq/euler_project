defmodule GCD do
  @moduledoc """
  求最大公约数
  """
  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))
end
