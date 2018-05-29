defmodule Euler147 do
  @moduledoc """
  https://projecteuler.net/problem=147
  """
  def horizontal_and_vertical(m, n), do: div(m * (m + 1) * n * (n + 1), 4)

  def diagonal(m, n) when m < n, do: diagonal(n, m)
  def diagonal(m, n), do: div(n * ((2 * m - n) * (4 * n * n - 1) - 3), 6)

  def solution() do
    for m <- 1..47,
         n <- 1..43 do
      {m, n}
    end
    |> Enum.map(fn {m, n} -> horizontal_and_vertical(m, n) + diagonal(m, n) end)
    |> Enum.sum()
  end
end
