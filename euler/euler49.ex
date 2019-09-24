defmodule Euler49 do
  @moduledoc """
  The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, 
  is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.
  There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.
  What 12-digit number do you form by concatenating the three terms in this sequence?
  """
  require Logger
  require Integer

  # 素数校验工具
  def prime?(n) when n < 2, do: false
  def prime?(2), do: true
  def prime?(n) when Integer.is_even(n), do: false

  def prime?(n), do: fermat_check(n, get_u(n - 1), 4)

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

  # === 全排列 ===

  def arrange_loop(acc) do
    receive do
      {:ok, digits} ->
        res = digits |> Enum.map(fn {_index, x} -> x end)

        cond do
          Enum.member?(acc, res) ->
            arrange_loop(acc)

          :else ->
            arrange_loop([res | acc])
        end

      {:finish, pid} ->
        send(pid, {:ok, acc})
    end
  end

  def full_arrange(list) do
    {:ok, pid} = Task.start_link(fn -> arrange_loop([]) end)
    perm(add_index(list, 0, []), [], pid, 0, length(list))
    send(pid, {:finish, self()})

    receive do
      {:ok, res} -> res
    end
  end

  defp add_index([], _, acc), do: acc
  defp add_index([h | t], index, acc), do: add_index(t, index + 1, [{index, h} | acc])

  def perm(_pool, _digits, _pid, deep, n) when deep > n, do: nil

  def perm(_pool, digits, pid, deep, n) when deep == n do
    send(pid, {:ok, digits})
  end

  def perm(pool, digits, pid, deep, n) do
    pool
    |> Enum.filter(fn x -> not Enum.member?(digits, x) end)
    |> Enum.map(fn x -> [x | digits] end)
    |> Enum.each(fn x -> perm(pool, x, pid, deep + 1, n) end)
  end

  ##  === 数字转列表，列表转数字 == 

  def num2list(num), do: n2l(num, [])
  defp n2l(0, acc), do: acc
  defp n2l(num, acc), do: n2l(div(num, 10), [rem(num, 10) | acc])

  def list2num(list), do: list |> Enum.reduce(0, fn x, acc -> acc * 10 + x end)

  # === 组合数 ===
  def combine_loop(acc) do
    receive do
      {:ok, digits} ->
        combine_loop([digits | acc])

      {:finish, pid} ->
        send(pid, {:ok, acc})
    end
  end

  defp in_order?([_]), do: true
  defp in_order?([h1, h2 | t]) when h1 >= h2, do: in_order?([h2 | t])
  defp in_order?(_), do: false

  defp combine(_pool, n, deep, _, _) when deep > n, do: nil

  defp combine(_pool, n, deep, digits, pid) when deep == n do
    send(pid, {:ok, digits})
  end

  defp combine(pool, n, deep, digits, pid) do
    pool
    |> Enum.filter(fn x -> not Enum.member?(digits, x) end)
    |> Enum.map(fn x -> [x | digits] end)
    |> Enum.filter(fn x -> in_order?(x) end)
    |> Enum.each(fn x -> combine(pool, n, deep + 1, x, pid) end)
  end

  def combine(list, c) do
    {:ok, pid} = Task.start_link(fn -> combine_loop([]) end)
    combine(list, c, 0, [], pid)
    send(pid, {:finish, self()})

    receive do
      {:ok, res} -> res
    end
  end

  #  解题部分

  def iter([], acc), do: acc

  def iter([h | t], acc) do
    case :ets.lookup(:euler49, h) do
      [] ->
        # miss
        nums =
          full_arrange(num2list(h))
          |> Enum.map(fn x -> list2num(x) end)
          |> Enum.filter(fn x -> x > 1000 end)
          |> Enum.filter(fn x -> prime?(x) end)

        cond do
          Enum.count(nums) >= 3 ->
            ress = combine(nums, 3) |> Enum.filter(fn x -> common_diff?(x) end)

            cond do
              Enum.count(ress) > 0 ->
                # add to jump cache
                nums |> Enum.each(fn x -> :ets.insert(:euler49, {x, 1}) end)
                [res] = ress
                iter(t, [res | acc])

              :else ->
                # add to jump cache
                nums |> Enum.each(fn x -> :ets.insert(:euler49, {x, 1}) end)
                iter(t, acc)
            end

          :else ->
            # add to jump cache
            nums |> Enum.each(fn x -> :ets.insert(:euler49, {x, 1}) end)
            iter(t, acc)
        end

      _ ->
        # in jump cache
        iter(t, acc)
    end
  end

  defp common_diff?([a, b, c]), do: a + c == b + b

  def now(), do: :os.system_time(:milli_seconds)
  
  def run() do
    start = now()
    # cache
    :ets.new(:euler49, [:named_table])

    res = 1000..9999
    |> Enum.filter(fn x -> prime?(x) end)
    |> iter([])
    |> Enum.map(fn x -> Enum.sort(x) end)
    |> Enum.map(fn x -> Enum.reduce(x, 0, fn y, acc -> acc * 10000 + y end) end)
    IO.inspect(res)
    timeuse = now() - start
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
