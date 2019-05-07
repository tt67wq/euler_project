defmodule Euler198 do
  @moduledoc false

  @limit 1000
  require Logger

  # 52374425

  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  def ambiguous?({p, q}) do
    d = div(q, p)

    cond do
      (q - p * d) * (d + 1) == (p * (d + 1) - q) * d ->
        {{1, d + 1}, {1, d}}

      :else ->
        approximations({p, q}, {1, d + 1}, {1, d}, {1, d}, q - p * d)
    end
  end

  defp approximations({p, q}, _, _, {p, q}, _), do: nil

  defp approximations({p, q}, {n1, m1}, {n2, m2}, {best_n, best_m}, db) do
    g = gcd(n1 + n2, m1 + m2)
    m3 = div(m1 + m2, g)

    n3 = div(n1 + n2, g)
    d3 = p * m3 - q * n3

    cond do
      abs(d3) * best_m == abs(db) * m3 ->
        {{best_n, best_m}, {n3, m3}}

      :else ->
        {new_best, new_db} =
          cond do
            abs(d3) * best_m < abs(db) * m3 ->
              {{n3, m3}, d3}

            :else ->
              {{best_n, best_m}, db}
          end

        cond do
          d3 > 0 ->
            approximations({p, q}, {n3, m3}, {n2, m2}, new_best, new_db)

          :else ->
            approximations({p, q}, {n1, m1}, {n3, m3}, new_best, new_db)
        end
    end
  end

  def run() do
    for q <- 101..@limit,
        p <- 1..div(q, 100) do
      {p, q, gcd(p, q)}
    end
    |> Enum.filter(fn {_, _, g} -> g == 1 end)
    |> Enum.filter(fn {p, q, _} -> ambiguous?({p, q}) != nil end)
  end
end
