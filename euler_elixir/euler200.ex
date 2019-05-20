defmodule Euler200 do
  @moduledoc false

  require Integer
  require Logger
  use Bitwise

  ####### prime check start
  def prime?(n) when n < 2, do: false
  def prime?(2), do: true
  def prime?(n) when Integer.is_even(n), do: false

  def prime?(n), do: fermat_check(n, get_u(n - 1), 5)

  defp fermat_check(_, _, 0), do: true

  defp fermat_check(n, u, s) do
    a = Enum.random(2..(n - 1))
    x = pow_mod(a, u, n)
    {flag, nx} = double_check(u, n, x)

    case flag do
      true ->
        case nx do
          1 -> fermat_check(n, u, s - 1)
          _ -> false
        end

      false ->
        false
    end
  end

  defp double_check(tu, n, x) when tu >= n, do: {true, x}

  defp double_check(tu, n, x) do
    y = Integer.mod(x * x, n)

    cond do
      y == 1 and x != 1 and x != n - 1 -> {false, 0}
      :else -> double_check(tu * 2, n, y)
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

  defp get_u(u) do
    case rem(u, 2) do
      0 -> get_u(div(u, 2))
      1 -> u
    end
  end

  ####### prime check end

  ####### Sieve start

  def sieve(max) do
    ops = sieve(max, 3, :array.new(max, {:default, 1}))

    res =
      3..max
      |> Enum.filter(fn x -> rem(x, 2) == 1 end)
      |> Enum.filter(fn x -> in_sieve?(ops, x) end)

    [2 | res]
  end

  defp sieve(max, i, acc) when i * i > max, do: acc

  defp sieve(max, i, acc) do
    case in_sieve?(acc, i) do
      true ->
        sieve(max, i + 2, remove(i, i * i, max, acc))

      _ ->
        sieve(max, i + 2, acc)
    end
  end

  defp remove(_, j, max, acc) when j > max, do: acc

  defp remove(i, j, max, acc), do: remove(i, j + bsl(i, 1), max, remove_from_sieve(acc, j))

  defp pos_fix(i), do: i |> bsr(1) |> bsl(1)

  @spec in_sieve?(term(), integer) :: boolean()
  def in_sieve?(sieve, i) do
    a = :array.get(i, sieve)

    b = pos_fix(i)

    (a &&& b) == 0
  end

  @spec remove_from_sieve(term(), integer) :: term()
  def remove_from_sieve(sieve, i) do
    a = :array.get(i, sieve)
    b = pos_fix(i)

    :array.set(i, bor(a, b), sieve)
  end

  ####### Sieve end

  def num2digits(num), do: n2d(num, 0, :array.new({:default, 0}))
  defp n2d(0, _, acc), do: acc

  defp n2d(num, index, acc),
    do: n2d(div(num, 10), index + 1, :array.set(index, rem(num, 10), acc))

  def digits2num(digits), do: d2n(:array.to_list(digits) |> Enum.reverse(), 0)
  defp d2n([], acc), do: acc
  defp d2n([h | t], acc), do: d2n(t, acc * 10 + h)

  def num_cluster(num, 0) do
    vec = num2digits(num)
    origin = :array.get(0, vec)

    [1, 3, 5, 7, 9]
    |> Enum.filter(fn x -> x != origin end)
    |> Enum.map(fn x -> :array.set(0, x, vec) end)
    |> Enum.map(fn x -> digits2num(x) end)
  end

  def vec_cluster(vec, pos) do
    origin = :array.get(pos, vec)

    0..9
    |> Enum.filter(fn x -> x != origin end)
    |> Enum.map(fn x -> :array.set(pos, x, vec) end)
    |> Enum.map(fn x -> digits2num(x) end)
  end

  def prime_in_cluster?(num) when rem(num, 2) == 0 do
    num_cluster(num, 0)
    |> Enum.any?(fn x -> prime?(x) end)
  end

  def prime_in_cluster(num) do
    vec = num2digits(num)
    pos_check(vec, :array.size(vec), 0)
  end

  defp pos_check(_, size, index) when index > size, do: false

  defp pos_check(vec, size, index) do
    ps = vec_cluster(vec, index)

    case Enum.any?(ps, fn x -> prime?(x) end) do
      true -> true
      _ -> pos_check(vec, size, index + 1)
    end
  end

  def contains200?(num) do
    num
    |> Integer.to_string()
    |> String.contains?("200")
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run(max) do
    ps = sieve(max)

    Stream.flat_map(ps, fn i ->
      Stream.flat_map(ps, fn j ->
        [{i, j}]
      end)
    end)
    |> Stream.map(fn {p, q} -> p * p * p * q * q end)
    |> Stream.filter(fn x -> contains200?(x) end)
    |> Stream.filter(fn x -> not prime_in_cluster(x) end)
    |> Enum.sort()
    |> Enum.take(200)
    |> Enum.to_list()

  end
end
