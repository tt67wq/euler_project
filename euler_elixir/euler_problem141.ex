defmodule Euler141 do
  @moduledoc """
  https://projecteuler.net/problem=141
  """
  require Integer
  require Logger
  @limit 1_000_000_000_000

  # def sqrt?(n), do: s?(n, 1)
  # defp s?(0, _), do: true
  # defp s?(n, _) when n < 0, do: false
  # defp s?(n, index), do: s?(n - index, index + 2)

  def sqrt?(n) do
    r = :math.sqrt(n) |> round()
    r * r == n
  end
  
  def extend({q, d, r, z}), do: ext({q, d, r, z}, 1, [])

  defp ext({q, d, r, _} = h, index, acc) do
    nz = q * d * index * index + r * index

    cond do
      nz > @limit -> acc
      sqrt?(nz) ->
	Logger.info("#{inspect {q * index, d * index, r * index, nz}}")
	ext(h, index + 1, [{q * index, d * index, r * index, nz} | acc])
      :else -> ext(h, index + 1, acc)
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
    |> Enum.reduce([], fn x, acc -> acc ++ extend(x) end)
    |> Enum.map(fn {_, _, _, x} -> x end)
    |> Enum.sort()
    |> Enum.dedup()
    |> Enum.sum()
  end
end
