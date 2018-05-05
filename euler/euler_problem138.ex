defmodule SpecialIsoscelesTriangles do
  @moduledoc """
  https://projecteuler.net/problem=138
  """
  @limit 10000
  require Integer

  def get_triangle_set(), do: gts(2, 1, [])

  defp gts(m, n, acc) when 2 * (n * n + m * m) > @limit, do: acc
  defp gts(m, n, acc) when n >= m, do: gts(m + 1, 1, acc)

  defp gts(m, n, acc) do
    cond do
      rem(m + n, 2) == 0 ->
        gts(m, n + 1, acc)

      :else ->
        cond do
          Integer.gcd(m, n) != 1 ->
            gts(m, n + 1, acc)

          :else ->
            a = m * m - n * n
            b = 2 * m * n
            c = m * m + n * n

            cond do
              a > b ->
                gts(m, n + 1, [{b, a, c} | acc])

              :else ->
                gts(m, n + 1, [{a, b, c} | acc])
            end
        end
    end
  end

  def solution() do
    get_triangle_set()
    |> Enum.sort_by(fn {x, _, _} -> x end)
    |> Enum.filter(fn {a, b, _} -> abs(b - 2 * a) == 1 end)
  end
end
