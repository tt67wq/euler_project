defmodule SubStringdivisibility do
  @moduledoc """
  https://projecteuler.net/problem=43
  """
  require Logger
  defp now(), do: :os.system_time(:milli_seconds)

  # 全排列
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

  # 列表到数字
  def list2num(list), do: l2n(list, 0)
  defp l2n([], acc), do: acc
  defp l2n([h | t], acc), do: l2n(t, acc * 10 + h)

  # 检测是否满足题目需求
  def check(_, []), do: true
  def check([], _), do: true
  def check([_a], _), do: true
  def check([_a, _b], _), do: true

  def check([a, b, c | t], [h | t1]) do
    cond do
      rem(list2num([a, b, c]), h) == 0 -> check([b, c | t], t1)
      :else -> false
    end
  end

  def loop_accept(acc, st) do
    receive do
      {:ok, [_ | t] = digits} ->
        cond do
          check(t, [2, 3, 5, 7, 11, 13, 17]) -> loop_accept([list2num(digits) | acc], st)
          :else -> loop_accept(acc, st)
        end

      {:finish} ->
        timeuse = now() - st
        s = Enum.sum(acc)
        IO.puts("result => #{s}, timecost => #{timeuse} milliseconds")
    end
  end

  def run() do
    start = now()
    {:ok, pid} = Task.start_link(fn -> loop_accept([], start) end)
    perm([1, 2, 3, 4, 5, 6, 7, 8, 9, 0], [], pid, 0, 10)
  end
end
