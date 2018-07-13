defmodule PythagoreanTiles do
  @moduledoc """
  https://projecteuler.net/problem=139
  """
  @limit 100_000_000

  def a(0), do: 0
  def a(1), do: 2
  def a(n), do: 6 * a(n - 1) - a(n - 2)

  def solution() do
    sl(2, [])
    |> Enum.map(fn x -> div(@limit, x) end)
    |> Enum.sum()
  end

  defp sl(index, acc) do
    num = a(index)

    cond do
      num > @limit -> acc
      :else -> sl(index + 1, [num | acc])
    end
  end
end
