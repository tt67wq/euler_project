defmodule Euler162 do
  @moduledoc """
  https://projecteuler.net/problem=162
  """
  require Integer
  require Logger

  def pow(_, 0), do: 1
  def pow(x, n) when Integer.is_odd(n), do: x * pow(x, n - 1)

  def pow(x, n) do
    result = pow(x, div(n, 2))
    result * result
  end

  def contains(list), do: ct(list, {0, 0, 0})

  defp ct([], {a, b, c}), do: a > 0 and b > 0 and c > 0

  defp ct([h | t], {a, b, c}) do
    case h do
      0 -> ct(t, {a + 1, b, c})
      1 -> ct(t, {a, b + 1, c})
      10 -> ct(t, {a, b, c + 1})
      _ -> ct(t, {a, b, c})
    end
  end

  # ----------- test -------------

  def startswith01(n), do: pow(16, n - 1) - pow(15, n - 1) * 2 + pow(14, n - 1)
  def startswithx(n), do: calculate_n(n - 1) * startswith01(n - 1)

  def calculate_n(3), do: 4

  def calculate_n(n) do
    case :ets.lookup(:euler162, n) do
      [{^n, value}] ->
        value

      [] ->
        v = 2 * startswith01(n) + 13 * startswithx(n)
        :ets.insert(:euler162, {n, v})
	v
    end
  end

  def run() do
    # for a <- 0..15,
    #     b <- 0..15,
    #     c <- 0..15,
    #     d <- 0..15 do
    #   [a, b, c, d]
    # end
    # |> Enum.filter(fn x -> contains(x) end)
    # |> Enum.filter(fn [h | _t] -> h != 0 end)
    # |> Enum.count()
    :ets.new(:euler162, [:named_table])
    calculate_n(3)
  end
end
