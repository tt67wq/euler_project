defmodule Euler57 do
  @moduledoc """
  https://projecteuler.net/problem=57
  """

  def m(1), do: {3, 2}

  def m(n) do
    {a, b} = cache_m(n - 1)
    {a + 2 * b, a + b}
  end

  def cache_m(n) do
    case :ets.lookup(:euler57, n) do
      [{^n, v}] ->
        v

      [] ->
        v = m(n)
        :ets.insert(:euler57, {n, v})
        v
    end
  end

  def digit_count(num), do: dc(num, 0)
  defp dc(0, acc), do: acc
  defp dc(num, acc), do: dc(div(num, 10), acc + 1)

  @spec now() :: integer()
  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    :ets.new(:euler57, [:named_table])

    res =
      1..1000
      |> Enum.map(fn x -> cache_m(x) end)
      |> Enum.filter(fn {a, b} -> digit_count(a) > digit_count(b) end)
      |> Enum.count()

    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
