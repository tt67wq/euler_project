defmodule Euler175 do
  @moduledoc """
  https://projecteuler.net/problem=175
  """
  require Logger
  require Integer

  def f(1), do: 1
  def f(2), do: 2

  def f(x) do
    case :ets.lookup(:euler175_2, x) do
      [{_, v}] ->
        v

      [] ->
        v =
          cond do
            rem(x, 2) == 0 ->
              # 偶数
              y = div(x, 2)
              f(y) + f(y - 1)

            :else ->
              # 奇数
              y = div(x + 1, 2)
              a(y)
          end

        :ets.insert(:euler175_2, {x, v})
        v
    end
  end

  def a(0), do: 0
  def a(1), do: 1

  def a(n) do
    case :ets.lookup(:euler175, n) do
      [{_, v}] ->
        v

      [] ->
        v =
          cond do
            rem(n, 2) == 0 ->
              a(div(n, 2))

            rem(n, 2) == 1 ->
              m = div(n - 1, 2)
              a(m) + a(m + 1)
          end

        :ets.insert(:euler175, {n, v})
        v
    end
  end

  def init() do
    :ets.new(:euler175, [:named_table])
    :ets.new(:euler175_2, [:named_table])
  end

  def now(), do: :os.system_time(:milli_seconds)

  def g(n) do
    a = f(2 * n + 1)
    b = f(2 * n)
    s = Integer.gcd(a, b)
    {div(a, s), div(b, s), div(b, s) - div(a, s)}
  end

  def test() do
    1..1000
    |> Enum.map(fn x -> {x, g(x)} end)
    |> Enum.filter(fn {_, {_, _, x}} -> x == 4 end)
  end
end
