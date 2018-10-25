defmodule Euler160 do
  @moduledoc """
  https://projecteuler.net/problem=160
  """
  require Integer
  require Logger

  @m 100_000

  def now(), do: :os.system_time(:milli_seconds)

  def trip_zero(n) do
    cond do
      rem(n, 10) == 0 -> trip_zero(div(n, 10))
      :else -> rem(n, @m)
    end
  end

  def g(x), do: trip_zero(x)

  def f(1), do: 1
  def f(n), do: fi(n, 1, 1)

  defp fi(n, index, acc) when index == n, do: acc
  defp fi(n, index, acc), do: fi(n, index + 1, g(acc * g(index + 1)))

  def run() do
    start = now()
    timeuse = now() - start
    res = f(1_000_000_000_000)
    IO.inspect(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
