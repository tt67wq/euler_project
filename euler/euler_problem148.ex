defmodule Euler148 do
  @moduledoc """
  https://projecteuler.net/problem=148
  """
  @limit 1_000_000
  require Logger

  # def cmob(_, 0, _), do: 1
  # def cmob(n, k, _p) when n < k, do: 0
  # def cmob(n, k, p), do: rem(cmob(n - 1, k - 1, p) + cmob(n - 1, k, p), p)

  def row_mod_count(n, p), do: rmc(n, p, 0, [1], 0)
  defp rmc(n, _p, index, _rows, acc) when index > n, do: acc
  defp rmc(n, p, 0, _, _), do: rmc(n, p, 1, [1, 1], 1)

  defp rmc(n, p, index, rows, acc) do    
    nrows = grows(rows) |> Enum.map(fn x -> rem(x, p) end)
    b = rows |> Enum.count(fn x -> rem(x, p) > 0 end)
    Logger.info("rows: #{index}, count: #{b}")
    rmc(n, p, index + 1, nrows, acc + b)
  end

  def grows(rows), do: gr(rows, [1])
  defp gr([h], acc), do: [h | acc]
  defp gr([h1, h2 | t], acc), do: gr([h2 | t], [h1 + h2 | acc])

  def solution(), do: row_mod_count(@limit - 1, 7)
end
