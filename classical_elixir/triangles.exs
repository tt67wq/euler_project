defmodule Triangles do
  @moduledoc """
  生成勾股数
  """
  @limit 500
  require Logger

  @doc """
  求最大公约数
  """
  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  def get_triangle_set() do
    gts(2, 1, [])
  end

  defp gts(m, n, acc) when 2 * (n * n + m * m) > @limit, do: acc
  defp gts(m, n, acc) when n >= m, do: gts(m + 1, 1, acc)

  defp gts(m, n, acc) do
    cond do
      rem(m + n, 2) == 0 ->
        gts(m, n + 1, acc)

      :else ->
        cond do
          gcd(m, n) != 1 ->
            gts(m, n + 1, acc)

          :else ->
            a = m * m - n * n
            b = 2 * m * n
            c = m * m + n * n
            gts(m, n + 1, [{a, b, c} | acc])
        end
    end
  end
end
