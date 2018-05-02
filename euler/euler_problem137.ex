defmodule FibonacciGoldenNuggets do
  @moduledoc """
  https://projecteuler.net/problem=137
  """
  require Integer
  require Logger

  def get_triangle_set() do
    gts(2, 1, [])
  end

  # defp gts(m, n, acc) when n * n + m * m > @limit, do: acc
  defp gts(m, n, acc) when n >= m, do: gts(m + 1, 1, acc)

  defp gts(m, n, acc) do
    a = m * m - n * n
    b = 2 * m * n
    c = m * m + n * n

    cond do
      length(acc) > 15 ->
        acc

      a < b ->
        cond do
          b == 2 * (a - 1) ->
            Logger.info("#{inspect({a, b, c})}")
            gts(m, n + 1, [{a, b, c} | acc])

          :else ->
            gts(m, n + 1, acc)
        end

      :else ->
        cond do
          a == 2 * (b - 1) ->
            Logger.info("#{inspect({b, a, c})}")
            gts(m, n + 1, [{b, a, c} | acc])

          :else ->
            gts(m, n + 1, acc)
        end
    end
  end

  def solution() do
    get_triangle_set()
    |> Stream.map(fn {a, b, c} -> {c - a, b} end)
    |> Stream.map(fn {m, n} -> div(m * n, n * n - m * n - m * m) end)
    |> Enum.to_list()
  end
end
