defmodule Euler192 do
  @limit 1_000_000_000_000

  require Logger

  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  def sqrt(n), do: round(Float.floor(:math.sqrt(n)))

  def is_sqrt?(n) do
    s = sqrt(n)
    s * s == n
  end

  defp approximations(target, {n1, m1}, {n2, m2}, {best_n, best_m}, db) do
    g = gcd(n1 + n2, m1 + m2)
    m3 = div(m1 + m2, g)

    cond do
      m3 > @limit ->
        {best_n, best_m}

      :else ->
        n3 = div(n1 + n2, g)
        d3 = target * m3 * m3 - n3 * n3
        # db = target * best_m * best_m - best_n * best_n

        {new_best, new_db} =
          cond do
            abs(d3) * best_m * best_m < abs(db) * m3 * m3 -> {{n3, m3}, d3}
            :else -> {{best_n, best_m}, db}
          end

        cond do
          d3 > 0 ->
            approximations(target, {n3, m3}, {n2, m2}, new_best, new_db)

          :else ->
            approximations(target, {n1, m1}, {n3, m3}, new_best, new_db)
        end
    end
  end

  def best_approximation(x) do
    sq = sqrt(x)
    db = x - sq * sq
    approximations(x, {sq, 1}, {sq + 1, 1}, {sq, 1}, db)
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      2..100_000
      |> Enum.filter(fn x -> not is_sqrt?(x) end)
      |> Enum.map(fn x ->
        # Logger.info(x)
        best_approximation(x)
      end)
      |> Enum.map(fn {_, m} -> m end)
      |> Enum.sum()

    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
