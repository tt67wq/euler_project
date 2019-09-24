defmodule Euler66 do
  @moduledoc """
  https://projecteuler.net/problem=66
  """
  @limit 80

  defp sqrt_floor(n), do: round(Float.floor(:math.sqrt(n)))

  def sqrt(num) do
    sf = sqrt_floor(num)
    sqrt_iter(num, sf, sf, 1, 0, [sf])
  end

  defp sqrt_iter(_m, _sf, _n, _k, @limit, acc), do: acc

  defp sqrt_iter(m, sf, n, k, index, acc) do
    nk = div(m - n * n, k)
    s = div(sf + n, nk)
    t = s * nk - n

    sqrt_iter(m, sf, t, nk, index + 1, [s | acc])
  end

  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  defp iter([h], {m, n}), do: {m + h * n, n}

  defp iter([h | t], {m, n}) do
    r = gcd(n, m + n * h)
    iter(t, {div(n, r), div(m + n * h, r)})
  end

  defp square(x), do: x * x

  def step_list(list), do: step(list, [])
  defp step([], acc), do: acc
  defp step([_ | t] = list, acc), do: step(t, [list | acc])

  defp search_satisfy(d, fs), do: Enum.find(fs, fn {m, n} -> m * m - n * n * d == 1 end)

  @spec now() :: integer()
  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      1..1000
      |> Enum.filter(fn x -> square(sqrt_floor(x)) != x end)
      |> Enum.map(fn x -> {x, sqrt(x)} end)
      |> Enum.map(fn {d, x} -> {d, step_list(x)} end)
      |> Enum.map(fn {d, x} -> {d, Enum.map(x, fn y -> iter(y, {0, 1}) end)} end)
      |> Enum.map(fn {d, fs} -> {d, search_satisfy(d, fs)} end)
      |> Enum.filter(fn {_d, x} -> x != nil end)
      |> Enum.max_by(fn {_, {x, _}} -> x end)

    IO.inspect(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
