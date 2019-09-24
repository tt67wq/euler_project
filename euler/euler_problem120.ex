defmodule SquareRemainders do
  @moduledoc """
  https://projecteuler.net/problem=120
  """

  @limit 1000
  
  def max_remainder(a), do: mr(a, 1, {1, 2*a})
  def mr(_, n, acc) when n > @limit, do: acc
  def mr(a, n, {i, acc}) do
    bcc = rem(2 * a * n, a * a)
    cond do
      bcc > acc -> mr(a, n+1, {n, bcc})
      :else -> mr(a, n+1, {i, acc})
    end
  end

  def solution() do
    3..1000 |> Enum.map(fn x -> max_remainder(x) end)
    |> Enum.map(fn {_, x} -> x end)
    |> Enum.sum
  end
end
