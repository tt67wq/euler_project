defmodule Euler160 do
  @moduledoc """
  https://projecteuler.net/problem=160
  """
  require Integer
  require Logger

  @m 100_000

  def now(), do: :os.system_time(:milli_seconds)

  def trip_zero(n) do
    cond do
      rem(n, 10) == 0 -> trip_zero(div(n, 10))
      :else -> n
    end
  end

  def g(x), do: trip_zero(x)

  # 同余定理
  def pow_mod(m, 1, k), do: Integer.mod(m, k)
  def pow_mod(m, 2, k), do: Integer.mod(m * m, k)

  def pow_mod(m, n, k) do
    t = Integer.mod(m, k)

    cond do
      t == 0 ->
        0

      :else ->
        cond do
          Integer.is_even(n) ->
            pow_mod(m, 2, k) |> pow_mod(div(n, 2), k)

          :else ->
            ((pow_mod(m, 2, k) |> pow_mod(div(n - 1, 2), k)) * t) |> Integer.mod(k)
        end
    end
  end

  def f(0), do: 1
  def f(1), do: 1
  def f(n), do: fi(n, 1, 1)

  defp fi(n, index, acc) when index == n, do: acc
  defp fi(n, index, acc), do: fi(n, index + 1, rem(g(acc * g(index + 1)), @m))

  # def run() do
  #   start = now()
  #   timeuse = now() - start
  #   res = rem(a(1_000_000_000_000) * b(1_000_000_000_000), @m)
  #   IO.inspect(res)
  #   IO.puts("timeuse => #{timeuse} milliseconds")
  # end

  def test(n) do
    res1 = f(n)
    res2 = rem(a(n) * b(n), @m)

    # 80000为例子，顺序不同，会导致结果不同
    # 这里需要好好思考下

    IO.puts("res1 = #{res1}, res2 = #{res2}")
  end

  def a(n) do
    cond do
      n > @m ->
        case rem(n, @m) do
          0 -> pow_mod(a(@m), div(n, @m), @m)
          _ -> rem(pow_mod(a(@m), div(n, @m), @m) * a(rem(n, @m)), @m)
        end

      :else ->
        1..n
        |> Enum.filter(fn x -> rem(x, 2) != 0 end)
        |> Enum.filter(fn x -> rem(x, 5) != 0 end)
        |> Enum.reduce(1, fn x, acc -> rem(acc * x, @m) end)
    end
  end

  def b(n) do
    cond do
      n > @m ->
        case rem(n, @m) do
          0 -> pow_mod(b(@m), div(n, @m), @m)
          _ -> rem(pow_mod(b(@m), div(n, @m), @m) * b(rem(n, @m)), @m)
        end

      :else ->
	# 这里不能简单的去除末尾的0
	# 会导致结果不正确
        1..n
        |> Enum.filter(fn x -> rem(x, 2) == 0 or rem(x, 5) == 0 end)
        |> Enum.reduce(1, fn x, acc -> rem(g(acc * x), @m) end)
    end
  end
end
