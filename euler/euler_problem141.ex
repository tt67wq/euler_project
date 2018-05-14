defmodule Euler141 do
  @moduledoc """
  https://projecteuler.net/problem=141
  """
  require Integer
  require Logger
  @limit 1_000_000_000_000

  def sqrt?(n), do: s?(n, 1)
  defp s?(0, _), do: true
  defp s?(n, _) when n < 0, do: false
  defp s?(n, index), do: s?(n - index, index + 2)

  def generate_sequnce({q, d, r, re}), do: gs({q, d, r, re}, 1, [])

  defp gs({q, d, r, re}, index, acc) do
    nre = index * index * q * d + index * r

    cond do
      nre > @limit ->
        acc

      :else ->
        cond do
          sqrt?(nre) ->
            gs({q, d, r, re}, index + 1, [{index * q, index * d, index * r, nre} | acc])

          :else ->
            gs({q, d, r, re}, index + 1, acc)
        end
    end
  end

  defp gp(q, _, acc) when q >= 10000, do: acc
  defp gp(q, r, acc) when r >= q, do: gp(q + 1, 1, acc)

  defp gp(q, r, acc) do
    g = Integer.gcd(q, r)

    case g do
      1 ->
        z = q * q * q * r + r * r

        cond do
          z > @limit ->
            acc

          :else ->
            gp(q, r + 1, [{q * q, q * r, r * r, z} | acc])
        end

      _ ->
        gp(q, r + 1, acc)
    end
  end

  def solution() do
    gp(2, 1, [])
    |> Enum.reduce([], fn x, acc -> generate_sequnce(x) ++ acc end)
    |> Enum.sort_by(fn {_, _, _, x} -> x end)
    |> Enum.dedup()

    # |> Enum.sum()
  end
end
