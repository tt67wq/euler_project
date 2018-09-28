defmodule Combination do
  @moduledoc """
  组合
  """

  def loop_accept() do
    receive do
      {:ok, digits} ->
        IO.inspect(digits)
        loop_accept()
    end
  end

  defp in_order?([_]), do: true
  defp in_order?([h1, h2 | t]) when h1 >= h2, do: in_order?([h2 | t])
  defp in_order?(_), do: false

  defp combine(_pool, n, deep, _, _) when deep > n, do: nil

  defp combine(_pool, n, deep, digits, pid) when deep == n do
    send(pid, {:ok, digits})
    :ok
  end

  defp combine(pool, n, deep, digits, pid) do
    pool
    |> Enum.filter(fn x -> not Enum.member?(digits, x) end)
    |> Enum.map(fn x -> [x | digits] end)
    |> Enum.filter(fn x -> in_order?(x) end)
    |> Enum.map(fn x -> combine(pool, n, deep + 1, x, pid) end)

    :ok
  end

  def run() do
    {:ok, pid} = Task.start_link(fn -> loop_accept() end)
    combine([1, 2, 3, 4], 3, 0, [], pid)
  end
end
