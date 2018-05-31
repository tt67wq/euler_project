defmodule Euler148 do
  @moduledoc """
  https://projecteuler.net/problem=148
  """
  @limit 50
  require Logger

  def choose(n, k), do: choose(n, k, {1, 1})
  defp choose(_, 0, {a, b}), do: div(a, b)
  defp choose(n, k, {a, b}), do: choose(n - 1, k - 1, {a * n, b * k})

  def row(n), do: 0..n |> Enum.map(fn x -> choose(n, x) end)

  def solution(), do: sl(0, 0, @limit)

  defp sl(index, acc, limit) when index >= limit, do: acc

  defp sl(index, acc, limit) do
    n =
      row(index)
      |> Enum.filter(fn x -> rem(x, 7) != 0 end)
      |> Enum.count()

     sl(index + 1, acc + n, limit)
  end
end
