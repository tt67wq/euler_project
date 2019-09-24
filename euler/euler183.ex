defmodule Euler183 do
  @moduledoc """
  https://projecteuler.net/problem=183
  """
  require Logger
  require Integer

  defp log(n), do: :math.log(n)

  # find k
  def foo(n) do
    l = log(n)

    1..n
    |> Enum.max_by(fn x -> x * (l - log(x)) end)
  end

  def bar(n) do
    l = log(n)
    df = fn x -> l - log(x) - 1 end

    search(df, 1, n)
    |> Enum.max_by(fn x -> x * (l - log(x)) end)
  end

  defp search(_, s, e) when s == e - 1, do: [s, e]

  defp search(f, s, e) do
    mid = div(s + e, 2)
    fm = f.(mid)

    cond do
      fm > 0 -> search(f, mid, e)
      fm < 0 -> search(f, s, mid)
      fm == 0 -> [mid]
    end
  end

  def contains_only_2_and_5(n) do
    r =
      wipe(n, 2)
      |> wipe(5)

    r == 1
  end

  defp wipe(n, p) do
    case rem(n, p) do
      0 -> wipe(div(n, p), p)
      _ -> n
    end
  end

  def d(n) do
    k = bar(n)

    g = Integer.gcd(n, k)

    cond do
      contains_only_2_and_5(div(k, g)) -> -n
      :else -> n
    end
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run do
    start = now()

    res =
      5..10000
      |> Enum.map(fn x -> d(x) end)
      |> Enum.sum()

    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
