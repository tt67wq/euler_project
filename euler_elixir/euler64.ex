defmodule Euler64 do
  @moduledoc """
  https://projecteuler.net/problem=64
  """

  require Logger

  defp sqrt_floor(n), do: round(Float.floor(:math.sqrt(n)))

  def sqrt(num) do
    sf = sqrt_floor(num)
    sqrt_iter(num, sf, sf, 1, MapSet.new(), [sf])
  end

  defp sqrt_iter(m, sf, n, k, set, acc) do
    nk = div(m - n * n, k)
    s = div(sf + n, nk)
    t = s * nk - n

    cond do
      MapSet.member?(set, {t, nk}) ->
        acc

      :else ->
        sqrt_iter(m, sf, t, nk, MapSet.put(set, {t, nk}), [s | acc])
    end
  end

  defp square(x), do: x * x

  @spec now() :: integer()
  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      1..10000
      |> Enum.filter(fn x -> square(sqrt_floor(x)) != x end)
      |> Enum.filter(fn x -> rem(Enum.count(sqrt(x)) - 1, 2) == 1 end)
      |> Enum.count()

    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
