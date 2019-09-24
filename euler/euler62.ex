defmodule Euler62 do
  @moduledoc """
  https://projecteuler.net/problem=62
  """

  defp digits(n), do: dts(n, [])
  defp dts(0, acc), do: Enum.sort(acc)
  defp dts(n, acc), do: dts(div(n, 10), [rem(n, 10) | acc])

  def cube_digits(n) do
    cb = n * n * n
    {cb, digits(cb)}
  end

  def search([]), do: nil

  def search([{n, ds} | t]) do
    rs = Enum.filter(t, fn {_, x} -> x == ds end)

    cond do
      Enum.count(rs) == 4 -> n
      :else -> search(Enum.filter(t, fn {_, x} -> x != ds end))
    end
  end

  @spec now() :: integer()
  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      1000..10000
      |> Enum.map(fn x -> cube_digits(x) end)
      |> search()

    IO.puts(res)

    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
