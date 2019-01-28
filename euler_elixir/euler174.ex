defmodule Euler174 do
  @moduledoc """
  https://projecteuler.net/problem=174
  """
  defp iter(1, b, top, acc) when b > top, do: acc
  defp iter(a, b, top, acc) when a >= b, do: iter(1, b + 1, top, acc)

  defp iter(a, b, top, acc) do
    cond do
      a * b <= top -> iter(a + 1, b, top, Map.update(acc, a * b, 1, fn y -> y + 1 end))
      :else -> iter(1, b + 1, top, acc)
    end
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      iter(1, 1, 250_000, %{})
      |> Map.to_list()
      |> Enum.filter(fn {_t, c} -> c >= 1 and c <= 10 end)
      |> Enum.count()

    IO.inspect(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
