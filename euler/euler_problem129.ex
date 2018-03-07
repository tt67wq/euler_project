defmodule RepunitDivisibility do
  @moduledoc """
  https://projecteuler.net/problem=129
  """
  require Integer
  require Logger
  @limit 1_000_000

  def a(n) do
    case Integer.gcd(n, 10) do
      1 -> a(n, 1, 1)
      _ -> 0
    end
  end

  defp a(_n, 0, acc), do: acc
  defp a(n, x, acc), do: a(n, rem(10 * x + 1, n), acc + 1)

  def solution(), do: sl(@limit + 1)

  defp sl(index) do
    an = a(index)

    cond do
      an > @limit -> index
      :else -> sl(index + 2)
    end
  end
end
