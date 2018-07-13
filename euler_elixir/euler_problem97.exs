defmodule LargeNonMersennePrime do
  @moduledoc """
  https://projecteuler.net/problem=97
  28433×2^7830457+1
  """
  @limit 7830457
  @base 10000000000

  def product_mod(a, b) do
    p = rem(a, @base) * rem(b, @base)
    cond do
      p > @base -> rem(p, @base)
      :else -> p
    end
  end

  def solution() do
    p = sl(2, 1)
    product_mod(p, 28433) + 1
  end

  defp sl(a, @limit), do: a
  defp sl(a, count), do: sl(product_mod(a, 2), count + 1)
end
