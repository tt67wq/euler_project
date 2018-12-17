defmodule Euler56 do
  @moduledoc """
  https://projecteuler.net/problem=56
  """

  require Integer

  def pow(_, 0), do: 1
  def pow(x, n) when Integer.is_odd(n), do: x * pow(x, n - 1)

  def pow(x, n) do
    result = pow(x, div(n, 2))
    result * result
  end

  def digit_sum(num), do: ds(num, 0)
  defp ds(0, acc), do: acc
  defp ds(num, acc), do: ds(div(num, 10), acc + rem(num, 10))

  @spec now() :: integer()
  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      for a <- 2..99,
          b <- 2..99 do
        pow(a, b)
        |> digit_sum()
      end
      |> Enum.max()

    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
