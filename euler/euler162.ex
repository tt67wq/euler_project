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

  def startswithA1(n), do: pow(16, n - 1) - pow(15, n - 1) * 2 + pow(14, n - 1)

  def startswithx(3), do: 0
  def startswithx(n), do: calculate_n(n - 1) + startswithA1(n - 1)

  def calculate_n(3), do: 4

  def calculate_n(n) do
    case :ets.lookup(:euler162, n) do
      [{^n, value}] ->
        value

      [] ->
        v = 2 * startswithA1(n) + 13 * startswithx(n)
        :ets.insert(:euler162, {n, v})
        v
    end
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    :ets.new(:euler162, [:named_table])

    res =
      3..16
      |> Enum.map(fn x -> calculate_n(x) end)
      |> Enum.sum()
      |> Integer.to_string(16)

    IO.puts(res)
    timeuse = now() - start
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
