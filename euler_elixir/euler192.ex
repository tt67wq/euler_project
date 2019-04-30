defmodule Euler192 do
  @limit 1_000_000_000_000

  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  def sqrt(n), do: round(:math.sqrt(n))

  def is_sqrt?(n) do
    s = sqrt(n)
    s * s == n
  end

  def approximations(target, {n1, m1}, {n2, m2}, {best_n, best_m}) do
    g = gcd(n1 + n2, m1 + m2)
    m3 = div(m1 + m2, g)

    cond do
      m3 > @limit ->
        {best_n, best_m}

      :else ->
        n3 = div(n1 + n2, g)
        d1 = target - :math.pow(n3 / m3, 2)
        d2 = abs(target - :math.pow(best_n / best_m, 2))

        new_best =
          cond do
            d2 > abs(d1) -> {n3, m3}
            :else -> {best_n, best_m}
          end

        cond do
          d1 > 0 ->
            approximations(target, {n3, m3}, {n2, m2}, new_best)

          :else ->
            approximations(target, {n1, m1}, {n3, m3}, new_best)
        end
    end
  end

  def run() do
    2..100_001
    |> Enum.filter(fn x -> not is_sqrt?(x) end)
    |> Enum.map(fn x -> approximations(x, {sqrt(x), 1}, {sqrt(x) + 1, 1}, {sqrt(x), 1}) end)
    |> Enum.map(fn {_, m} -> m end)
    |> Enum.sum()
  end
end
