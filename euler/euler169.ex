defmodule Euler169 do
  @moduledoc """
  https://projecteuler.net/problem=169
  """

  require Integer
  require Logger

  def pow(_, 0), do: 1
  def pow(x, n) when Integer.is_odd(n), do: x * pow(x, n - 1)

  def pow(x, n) do
    result = pow(x, div(n, 2))
    result * result
  end

  def f(1), do: 1
  def f(2), do: 2

  def f(x) do
    case :ets.lookup(:euler169_2, x) do
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

        :ets.insert(:euler169_2, {x, v})
        v
    end
  end

  def a(0), do: 0
  def a(1), do: 1

  def a(n) do
    case :ets.lookup(:euler169, n) do
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

        :ets.insert(:euler169, {n, v})
        v
    end
  end

  def init() do
    :ets.new(:euler169, [:named_table])
    :ets.new(:euler169_2, [:named_table])
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    init()

    res =
      pow(10, 25)
      |> f()

    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
