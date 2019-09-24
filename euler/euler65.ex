defmodule Euler65 do
  @moduledoc """
  https://projecteuler.net/problem=65
  """
  require Logger

  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  defp iter([h], {m, n}), do: {m + h * n, n}

  defp iter([h | t], {m, n}) do
    r = gcd(n, m + n * h)
    iter(t, {div(n, r), div(m + n * h, r)})
  end

  def e_fraction(), do: Enum.reverse(ef(1, [2]))
  defp ef(35, acc), do: acc
  defp ef(index, acc), do: ef(index + 1, [1, 2 * index, 1 | acc])

  def digit_sum(num), do: ds(num, 0)
  defp ds(0, acc), do: acc
  defp ds(num, acc), do: ds(div(num, 10), acc + rem(num, 10))

  @spec now() :: integer()
  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    nums = e_fraction() |> Enum.take(100) |> Enum.reverse()
    {m, _} = iter(nums, {0, 1})
    res = digit_sum(m)
    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
