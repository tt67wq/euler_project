defmodule Euler166 do
  @moduledoc """
  https://projecteuler.net/problem=166
  """
  require Logger

  @upper 9

  def bfs(pid, s, 8, %{0 => a0, 4 => a4} = acc) do

    0..min(@upper, s - a0 - a4)
    |> Enum.map(fn x -> Map.put(acc, 8, x) end)
    |> Enum.map(fn %{0 => a0, 4 => a4, 8 => a8} = x -> Map.put(x, 12, s - a0 - a4 - a8) end)
    |> Enum.filter(fn %{12 => a12} -> a12 >= 0 and a12 <= 9 end)
    |> Enum.map(fn %{3 => a3, 6 => a6, 12 => a12} = x -> Map.put(x, 9, s - a3 - a6 - a12) end)
    |> Enum.filter(fn %{9 => a9} -> a9 >= 0 and a9 <= 9 end)
    |> Enum.map(fn %{1 => a1, 5 => a5, 9 => a9} = x -> Map.put(x, 13, s - a1 - a5 - a9) end)
    |> Enum.filter(fn %{13 => a13} -> a13 >= 0 and a13 <= 9 end)
    |> Enum.map(fn %{0 => a0, 5 => a5, 8 => a8, 9 => a9, 3 => a3, 7 => a7} = x ->
      Map.put(x, 10, s - a0 - a5 - a8 - a9 + a3 + a7)
    end)
    |> Enum.filter(fn %{10 => b10} -> b10 >= 0 and rem(b10, 2) == 0 end)
    |> Enum.map(fn %{10 => b10} = x -> Map.put(x, 10, div(b10, 2)) end)
    |> Enum.map(fn %{2 => a2, 6 => a6, 10 => a10} = x -> Map.put(x, 14, s - a2 - a6 - a10) end)
    |> Enum.filter(fn %{14 => a14} -> a14 >= 0 and a14 <= 9 end)
    |> Enum.map(fn %{8 => a8, 9 => a9, 10 => a10} = x -> Map.put(x, 11, s - a8 - a9 - a10) end)
    |> Enum.filter(fn %{11 => a11} -> a11 >= 0 and a11 <= 9 end)
    |> Enum.map(fn %{0 => a0, 5 => a5, 10 => a10} = x -> Map.put(x, 15, s - a0 - a5 - a10) end)
    |> Enum.filter(fn %{15 => a15} -> a15 >= 0 and a15 <= 9 end)
    |> Enum.filter(fn %{12 => a12, 13 => a13, 14 => a14, 15 => a15} ->
      s == a12 + a13 + a14 + a15
    end)
    |> Enum.each(fn x -> send(pid, {:ok, x}) end)
  end

  def bfs(pid, s, 6, %{4 => a4, 5 => a5} = acc) do
    0..min(s - a4 - a5, @upper)
    |> Enum.map(fn x -> Map.put(acc, 6, x) end)
    |> Enum.map(fn %{4 => a4, 5 => a5, 6 => a6} = x -> Map.put(x, 7, s - a4 - a5 - a6) end)
    |> Enum.filter(fn %{7 => a7} -> a7 >= 0 and a7 <= 9 end)
    |> Enum.each(fn x -> bfs(pid, s, 8, x) end)
  end

  def bfs(pid, s, 5, %{4 => a4} = acc) do
    0..min(s - a4, @upper)
    |> Enum.map(fn x -> Map.put(acc, 5, x) end)
    |> Enum.each(fn x -> bfs(pid, s, 6, x) end)
  end

  def bfs(pid, s, 4, acc) do
    0..min(s, @upper)
    |> Enum.map(fn x -> Map.put(acc, 4, x) end)
    |> Enum.each(fn x -> bfs(pid, s, 5, x) end)
  end

  def bfs(pid, _, 3, acc) do
    0..@upper
    |> Enum.map(fn x -> Map.put(acc, 3, x) end)
    |> Enum.each(fn x -> bfs(pid, get_s(x), 4, x) end)
  end

  def bfs(pid, s, deep, acc) do
    0..@upper
    |> Enum.map(fn x -> Map.put(acc, deep, x) end)
    |> Enum.each(fn x -> bfs(pid, s, deep + 1, x) end)
  end

  defp get_s(mp) do
    %{0 => a0, 1 => a1, 2 => a2, 3 => a3} = mp
    a0 + a1 + a2 + a3
  end

  def loop_accept(acc) do
    receive do
      {:ok, res} ->
        res =
          Map.to_list(res)
          |> Enum.map(fn {_, x} -> x end)
          |> Enum.join()

        Logger.info("#{res}")
        loop_accept(acc + 1)

      {:finish, pid} ->
        send(pid, {:ok, acc})
    end
  end

  def run() do
    {:ok, pid} = Task.start(fn -> loop_accept(0) end)
    bfs(pid, 0, 0, %{})

    send(pid, {:finish, self()})

    receive do
      {:ok, res} ->
        Process.exit(pid, :kill)
        Enum.count(res)
    end
  end
end
