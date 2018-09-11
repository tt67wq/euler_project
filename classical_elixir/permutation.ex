defmodule Permutation do
  @moduledoc """
  全排列 
  """

  # 全排列
  require Logger

  def perm(_pool, _digits, _pid, deep, n) when deep > n, do: nil

  def perm(_pool, digits, pid, deep, n) when deep == n do
    send(pid, {:ok, digits})
  end

  def perm(pool, digits, pid, deep, n) do
    pool
    |> Enum.filter(fn x -> not Enum.member?(digits, x) end)
    |> Enum.map(fn x -> [x | digits] end)
    |> Enum.map(fn x -> perm(pool, x, pid, deep + 1, n) end)

    :ok
  end

  def loop_accept() do
    receive do
      {:ok, digits} ->
        Logger.info("#{inspect(digits)}")
        loop_accept()
    end
  end

  def run() do
    {:ok, pid} = Task.start_link(fn -> loop_accept() end)
    perm([1, 2, 3, 4], [], pid, 0, 4)
  end
end
