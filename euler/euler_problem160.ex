defmodule Euler160 do
  @moduledoc """
  https://projecteuler.net/problem=160
  """
  require Integer
  require Logger

  @m 100_000

  def now(), do: :os.system_time(:milli_seconds)

  # 拔除末尾的0
  def trip_zero(n) do
    cond do
      rem(n, 10) == 0 -> trip_zero(div(n, 10))
      :else -> n
    end
  end

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

  # 质因数分解
  @spec factorize(Integer) :: map()
  def factorize(num), do: factorize(num, 2, %{})

  defp factorize(num, index, acc) when index > num, do: acc

  defp factorize(num, index, acc) do
    case rem(num, index) do
      0 -> factorize(div(num, index), index, Map.update(acc, index, 1, fn x -> x + 1 end))
      _ -> factorize(num, index + 1, acc)
    end
  end

  def pow_factorize(num) do
    1..num
    |> Enum.map(fn x -> factorize(x) end)
    |> Enum.reduce(%{}, fn x, acc -> Map.merge(acc, x, fn _k, v1, v2 -> v1 + v2 end) end)
  end

  def f(n) do
    mp = pow_factorize(n)
    c2 = Map.get(mp, 2, 0)
    c5 = Map.get(mp, 5, 0)

    Map.drop(mp, [5])
    |> Map.put(2, c2 - c5)
    |> Map.to_list()
    |> Enum.map(fn {v, c} -> pow_mod(v, c, @m) end)
    |> Enum.reduce(1, fn x, acc -> rem(acc * x, @m) end)
  end

  def fast_f(n) when n < @m, do: f(n)
  def fast_f(n), do: rem(a(n) * fast_b(n), @m)

  # 1..n中所有不能被2和5整除的数字
  def a(n) when n > @m do
    case rem(n, @m) do
      0 -> pow_mod(a(@m), div(n, @m), @m)
      v -> rem(pow_mod(a(@m), div(n, @m), @m) * a(v), @m)
    end
  end

  def a(n) do
    1..n
    |> Enum.filter(fn x -> rem(x, 2) != 0 end)
    |> Enum.filter(fn x -> rem(x, 5) != 0 end)
    |> Enum.reduce(1, fn x, acc -> rem(acc * x, @m) end)
  end

  # 1..n中所有能被2或5整除的数字
  # def b(n) do
  #   mp =
  #     1..n
  #     |> Enum.filter(fn x -> rem(x, 2) == 0 or rem(x, 5) == 0 end)
  #     |> Enum.map(fn x -> factorize(x) end)
  #     |> Enum.reduce(%{}, fn x, acc -> Map.merge(acc, x, fn _k, v1, v2 -> v1 + v2 end) end)

  #   c2 = Map.get(mp, 2, 0)
  #   c5 = Map.get(mp, 5, 0)

  #   Map.drop(mp, [5])
  #   |> Map.put(2, c2 - c5)
  #   |> Map.to_list()
  #   |> Enum.map(fn {v, c} -> pow_mod(v, c, @m) end)
  #   |> Enum.reduce(1, fn x, acc -> rem(acc * x, @m) end)
  # end

  def fast_b(n) do
    a = fast_f(div(n, 5))
    b = c(div(n, 2))
    c = pow_mod(2, div(n, 5), @m)
    rem(a * b * c, @m)
  end

  def c(n) when n > @m do
    case rem(n, @m) do
      0 -> pow_mod(c(@m), div(n, @m), @m)
      v -> rem(pow_mod(c(@m), div(n, @m), @m) * c(v), @m)
    end
  end

  def c(n) do
    1..n
    |> Enum.filter(fn x -> rem(x, 5) != 0 end)
    |> Enum.reduce(1, fn x, acc -> rem(acc * x, @m) end)
  end

  def run() do
    start = now()    
    res = fast_f(1_000_000_000_000)
    timeuse = now() - start
    IO.puts(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
