defmodule Euler51 do
  @moduledoc """
  https://projecteuler.net/problem=51
  最小的数字，可替换位必然为1，2，3中的一个
  """
  require Logger
  require Integer

  # -------------------------- 质数工具函数 --------------------------
  require Integer
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

  # -------------------------- 质数工具函数 --------------------------

  # ----------- 全排列工具 start ------------
  def loop_accept(acc) do
    receive do
      {:ok, digits} ->
        res = digits |> Enum.map(fn {_index, x} -> x end)

        cond do
          Enum.member?(acc, res) ->
            loop_accept(acc)

          :else ->
            loop_accept([res | acc])
        end

      {:finish, pid} ->
        send(pid, {:ok, acc})
    end
  end

  defp add_index([], _, acc), do: acc
  defp add_index([h | t], index, acc), do: add_index(t, index + 1, [{index, h} | acc])

  def perm(_pool, _digits, _pid, deep, n) when deep > n, do: nil

  def perm(_pool, digits, pid, deep, n) when deep == n, do: send(pid, {:ok, digits})

  def perm(pool, digits, pid, deep, n) do
    pool
    |> Enum.filter(fn x -> not Enum.member?(digits, x) end)
    |> Enum.map(fn x -> [x | digits] end)
    |> Enum.each(fn x -> perm(pool, x, pid, deep + 1, n) end)
  end

  def arrange(list) do
    {:ok, pid} = Task.start(fn -> loop_accept([]) end)
    perm(add_index(list, 0, []), [], pid, 0, length(list))

    send(pid, {:finish, self()})

    receive do
      {:ok, res} ->
        Process.exit(pid, :kill)
        res
    end
  end

  # ----------- 全排列工具 end ------------

  # ----------- 置换工具 begin ------------
  defp replace1([], _, _, acc), do: Enum.reverse(acc)
  defp replace1([h | t], a, b, acc) when h == a, do: replace1(t, a, b, [b | acc])
  defp replace1([h | t], a, b, acc), do: replace1(t, a, b, [h | acc])

  # ----------- 置换工具 end   ------------

  defp list2int([], acc), do: acc
  defp list2int([h | t], acc), do: list2int(t, acc * 10 + h)

  @doc """
  生成mask
  l长度的数字和n个带渲染位
  最后一位必然不可被渲染
  """
  def generate_mask(l, n) do
    p1 = 1..n |> Enum.map(fn _ -> "x" end)
    p2 = 1..(l - n - 1) |> Enum.map(fn _ -> "y" end)

    arrange(p1 ++ p2)
    |> Enum.map(fn x -> x ++ ["y"] end)
  end

  @doc """
  渲染x
  """
  def rend_x(mask) do
    0..9
    |> Enum.map(fn x -> replace1(mask, "x", x, []) end)
    |> Enum.map(fn x -> list2int(x, 0) end)
    |> Enum.filter(fn x -> prime?(x) end)
  end

  @doc """
  渲染y
  """
  def rend_y(mask) do
    {:ok, pid} = Task.start(fn -> y_loop([]) end)
    rend(mask, [], pid)
    send(pid, {:finish, self()})

    receive do
      {:ok, res} ->
        Process.exit(pid, :kill)
        res
    end
  end

  defp y_loop(acc) do
    receive do
      {:ok, ele} -> y_loop([Enum.reverse(ele) | acc])
      {:finish, pid} -> send(pid, {:ok, acc})
    end
  end

  defp rend([], acc, pid), do: send(pid, {:ok, acc})

  defp rend(["y" | t], acc, pid) do
    0..9
    |> Enum.map(fn x -> [x | acc] end)
    |> Enum.each(fn x -> rend(t, x, pid) end)
  end

  defp rend([h | t], acc, pid), do: rend(t, [h | acc], pid)

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      generate_mask(6, 3)
      |> Enum.reduce([], fn x, acc -> rend_y(x) ++ acc end)
      |> Enum.map(fn x -> rend_x(x) end)
      |> Enum.filter(fn x -> length(x) >= 8 end)

    timeuse = now() - start
    IO.inspect(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
