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
      :else -> rem(n, @m)
    end
  end

  def g(x), do: trip_zero(x)

  def f(0), do: 1
  def f(1), do: 1  
  # def f(9), do: 36288
  # def f(99), do: 16864
  # def f(999), do: 53472
  def f(n), do: fi(n, 1, 1)

  defp fi(n, index, acc) when index == n, do: acc
  defp fi(n, index, acc), do: fi(n, index + 1, g(acc * g(index + 1)))

  # 数字长度
  def num_length(num), do: nl(num, 0)
  defp nl(0, acc), do: acc
  defp nl(num, acc), do: nl(div(num, 10), acc + 1)

  def split(n) do
    # 切分为n = a + b
    # 满足
    # a >> b a + b中间至少要有4个0
    # a = 100000 * k
    # 找出最大的b

    mk = div(n, @m)
    iter(n, mk)
  end

  defp iter(n, 0), do: {n, 0}

  defp iter(n, k) do
    a = k * @m
    b = n - a
    # Logger.info("#{a}, #{b}, #{n}")
    d = num_length(a) - num_length(b)

    case d do
      0 -> {n, 0}
      1 -> {n, 0}
      2 -> {n, 0}
      3 -> {n, 0}
      4 -> {n, 0}
      _ -> {a, b}
    end
  end

  def fast_f(n) do
    {a, b} = split(n)

    cond do
      a <= @m ->
        g(f(a) * f(b))

      b == 0 ->
        g(fast_f(a - 1) * g(a))

      :else ->
        Logger.info("#{a}, #{b}, #{n}")
        g(fast_f(a) * f(b))
    end
  end

  def run() do
    start = now()
    timeuse = now() - start
    res = fast_f(1_000_000_000_000)
    IO.inspect(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
