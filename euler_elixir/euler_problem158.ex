defmodule Euler158 do
  @moduledoc """
  https://projecteuler.net/problem=158
  """
  require Logger

  def perm(_pool, _digits, _pid, deep, n) when deep > n, do: nil

  def perm(_pool, digits, pid, deep, n) when deep == n do
    send(pid, {:ok, digits})
  end

  def perm(pool, digits, pid, deep, n) do
    pool
    |> Enum.filter(fn x -> not Enum.member?(digits, x) end)
    |> Enum.map(fn x -> [x | digits] end)
    |> Enum.filter(fn x -> lexicographically_times(x) <= 1 end)
    |> Enum.map(fn x -> perm(pool, x, pid, deep + 1, n) end)

    if deep == 0 do
      send(pid, {:finish})
    end

    :ok
  end

  def digit_encode(digits), do: encode(digits, [])
  defp encode([_], acc), do: Enum.reverse(acc)
  defp encode([h1, h2 | t], acc) when h1 > h2, do: encode([h2 | t], [1 | acc])
  defp encode([_h1, h2 | t], acc), do: encode([h2 | t], [0 | acc])

  def lexicographically_times(digits), do: once(digits, 0)
  defp once([_], acc), do: acc
  defp once([h1, h2 | t], acc) when h1 < h2, do: once([h2 | t], acc + 1)
  defp once([_, h | t], acc), do: once([h | t], acc)

  def loop_accept(acc, st) do
    receive do
      {:ok, digits} ->
        cond do
          lexicographically_times(digits) == 1 ->
            loop_accept([digit_encode(digits) | acc], st)

          :else ->
            loop_accept(acc, st)
        end

      {:finish} ->
        timeuse = now() - st
        s = Enum.count(acc)
        mp = acc |> Enum.reduce(%{}, fn x, acc -> Map.update(acc, x, 1, fn y -> y + 1 end) end)
        IO.puts("count => #{s}, timecost => #{timeuse} milliseconds")
	IO.inspect(mp)
    end
  end

  defp now(), do: :os.system_time(:milli_seconds)

  def run(base) do
    start = now()
    {:ok, pid} = Task.start_link(fn -> loop_accept([], start) end)
    perm(1..26, [], pid, 0, base)
  end
end
