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
            loop_accept([res | acc])
        end

      {:finish, pid} ->
        send(pid, {:ok, acc})
    end
  end

  defp add_index([], _, acc), do: acc
  defp add_index([h | t], index, acc), do: add_index(t, index + 1, [{index, h} | acc])

  def permutation(list) do
    {:ok, pid} = Task.start_link(fn -> loop_accept([]) end)
    perm(list |> add_index(0, []), [], pid, 0, Enum.count(list))
    send(pid, {:finish, self()})

    receive do
      {:ok, res} ->
        Process.exit(pid, :kill)
        res
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
    |> Enum.each(fn x -> perm(pool, x, pid, deep + 1, n) end)
  end

  #### 另外一种方法 #########

  def permutations(list) do
    list
    |> Enum.sort()
    |> Stream.unfold(fn
      [] -> nil
      p -> {p, next_permutation(p)}
    end)
  end

  defp next_permutation(permutation) do
    if permutation == permutation |> Enum.sort() |> Enum.reverse() do
      []
    else
      permutation
      |> split
      |> heal
    end
  end

  defp split(permutation) do
    permutation
    |> Enum.reverse()
    |> Enum.reduce({0, false, [], []}, fn x, {prev, split, first, last} ->
      case split do
        false -> {x, x < prev, first, [x | last]}
        true -> {x, true, [x | first], last}
      end
    end)
    |> (fn {_, _, first, last} -> {first, last} end).()
  end

  defp heal({first, [h | _] = last}) do
    next = last |> Enum.filter(&(&1 > h)) |> Enum.min()
    rest = (last -- [next]) |> Enum.sort()
    first ++ [next] ++ rest
  end

  ##### 反向 ############
  def reverse_permutations(list) do
    list
    |> Enum.sort()
    |> Enum.reverse()
    |> Stream.unfold(fn
      [] -> nil
      p -> {p, re_next_permutation(p)}
    end)
  end

  defp re_next_permutation(permutation) do
    if permutation == permutation |> Enum.sort() do
      []
    else
      permutation
      |> re_split
      |> re_heal
    end
  end

  defp re_split(permutation) do
    permutation
    |> Enum.reverse()
    |> Enum.reduce({20, false, [], []}, fn x, {prev, split, first, last} ->
      case split do
        false -> {x, x > prev, first, [x | last]}
        true -> {x, true, [x | first], last}
      end
    end)
    |> (fn {_, _, first, last} -> {first, last} end).()
  end

  defp re_heal({first, [h | _] = last}) do
    next = last |> Enum.filter(&(&1 < h)) |> Enum.max()
    rest = (last -- [next]) |> Enum.sort() |> Enum.reverse()
    first ++ [next] ++ rest
  end
end
