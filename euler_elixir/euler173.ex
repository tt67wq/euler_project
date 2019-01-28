defmodule Euler173 do
  @moduledoc """
  https://projecteuler.net/problem=173
  """
  defp iter(1, b, top, acc) when b > top, do: acc
  defp iter(a, b, top, acc) when a >= b, do: iter(1, b + 1, top, acc)

  defp iter(a, b, top, acc) do
    cond do
      a * b <= top -> iter(a + 1, b, top, acc + 1)
      :else -> iter(1, b + 1, top, acc)
    end
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    res = iter(1, 1, 250_000, 0)
    IO.inspect(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
