defmodule PandigitalPrime do
  @moduledoc """
  We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once.
  For example, 2143 is a 4-digit pandigital and is also prime.
  What is the largest n-digit pandigital prime that exists?
  """
  # 全排列
  require Logger
  require Integer
  def prime?(n) when n < 2, do: false
  def prime?(2), do: true
  def prime?(n) when Integer.is_even(n), do: false

  def prime?(n), do: fermat_check(n, get_u(n - 1), 3)

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
      1 -> get_u(div(u, 2))
      _ -> u
    end
  end

  def perm(_pool, _digits, _pid, deep, n) when deep > n, do: nil

  def perm(_pool, digits, pid, deep, n) when deep == n do
    send(pid, {:ok, digits})
  end

  def perm(pool, digits, pid, deep, n) do
    pool
    |> Enum.filter(fn x -> not Enum.member?(digits, x) end)
    |> Enum.map(fn x -> [x | digits] end)
    |> Enum.map(fn x -> perm(pool, x, pid, deep + 1, n) end)

    if deep == 0 do
      send(pid, {:finish})
    end

    :ok
  end

  def loop_accept(acc, st) do
    receive do
      {:ok, digits} ->
        num = list2num(digits)

        cond do
          prime?(num) ->
            loop_accept([num | acc], st)

          :else ->
            loop_accept(acc, st)
        end

      {:finish} ->
	timeuse = now() - st
	mx = Enum.max(acc)
	IO.puts("result => #{mx}, timecost => #{timeuse} microseconds")
    end
  end

  defp now(), do: :os.system_time(:micro_seconds)
  def list2num(list), do: l2n(list, 0)
  defp l2n([], acc), do: acc
  defp l2n([h | t], acc), do: l2n(t, acc * 10 + h)

  def run() do
    start = now()
    {:ok, pid} = Task.start_link(fn -> loop_accept([], start) end)
    perm([1, 2, 3, 4, 5, 6, 7], [], pid, 0, 7)
  end
end
