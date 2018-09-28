defmodule Permutation do
  @moduledoc """
  全排列 
  """
  def loop_accept(acc) do
    receive do
      {:ok, digits} ->
        res = digits |> Enum.map(fn {_index, x} -> x end)

        cond do
          Enum.member?(acc, res) ->
            loop_accept(acc)

          :else ->
            IO.inspect(res)
            loop_accept([res | acc])
        end
    end
  end

  defp add_index([], _, acc), do: acc
  defp add_index([h | t], index, acc), do: add_index(t, index + 1, [{index, h} | acc])

  def run() do
    {:ok, pid} = Task.start_link(fn -> loop_accept([]) end)
    perm([1, 2, 3, 3] |> add_index(0, []), [], pid, 0, 4)
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

    :ok
  end
end
