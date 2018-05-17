defmodule Euler143 do
  @moduledoc """
  https://projecteuler.net/problem=143
  """
  @limit 120000
  require Integer
  require Logger

  def sqrt?(n) do
    r = :math.sqrt(n) |> round()
    r * r == n
  end

  def check(p, q), do: (p * p + q * q + p * q) |> sqrt?()

  defp iter(p, 1, 1, acc) when p >= @limit - 1, do: acc
  defp iter(p, q, _, acc) when q > p, do: iter(p + 1, 1, 1, acc)
  defp iter(p, q, r, acc) when r > q, do: iter(p, q + 1, 1, acc)
  defp iter(p, q, r, acc) when p + q + r > @limit, do: iter(p, q + 1, 1, acc)

  defp iter(p, q, r, acc) do
    g1 = Integer.gcd(p, q) |> Integer.gcd(r)

    case g1 do
      1 ->
        cond do
          check(p, q) ->
            cond do
              check(q, r) and check(p, r) ->
                Logger.info("#{p},#{q},#{r}")
                iter(p + 1, 1, 1, [{p, q, r} | acc])

              :else ->
                iter(p, q, r + 1, acc)
            end

          :else ->
            iter(p, q + 1, 1, acc)
        end

      _ ->
        iter(p, q, 1 + r, acc)
    end
  end

  def extend({p, q, r}), do: extend({p, q, r}, 1, 0, [])

  defp extend({p, q, r}, index, sum, acc) do
    cond do
      sum + p + q + r > @limit ->
        acc

      :else ->
        extend({p, q, r}, index + 1, sum + p + q + r, [{p * index, q * index, r * index} | acc])
    end
  end

  def solution() do
    iter(1, 1, 1, [])
    |> Enum.reduce([], fn x, acc -> extend(x) ++ acc end)
    |> Enum.map(fn {p, q, r} -> p + q + r end)
    |> Enum.sum()
  end
end
