defmodule Testing do
  @moduledoc """
  https://projecteuler.net/problem=105
  """
  def solution() do
    {_, content} = File.read("p105_sets.txt")
    content |> String.split("\n")
    |> Enum.map(fn x -> x |> String.split(",") |> strings2ints end)
    |> Enum.filter(fn x -> x |> special? end)
    |> Enum.map(fn x -> x |> Enum.sum end)
  end

  def strings2ints(list), do: s2i(list, [])
  defp s2i([], acc), do: acc |> Enum.reverse
  defp s2i([h|t], acc), do: s2i(t, [h |> String.to_integer|acc])

  @doc """
  ## Example

      iex> Generator.choose([1,2,3], 2)
      [[1, 2], [1, 3], [2, 3]]
  """
  @spec choose(List, Integer) :: List
  def choose(lst, n), do: chs(lst, n) |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end) |> MapSet.to_list()
  defp chs(lst, n) when length(lst) == n, do: [lst]
  defp chs(lst, 1), do: lst |> Enum.map(fn x -> [x] end)
  defp chs([h|t], n), do: (choose(t, n-1) |> Enum.map(fn x -> [h|x] end)) ++ choose(t, n)
  
  def special?(list), do: special?(list, 1, length(list), 0)
  defp special?(_list, index, l, _m) when l == index, do: true
  defp special?(list, index, l, m) do
    cls = choose(list, index)
    ls = cls |> Enum.map(fn x -> x |> Enum.sum end) |> Enum.sort |> Enum.dedup
    cond do
      length(ls) != length(cls) -> false
      List.first(ls) <= m -> false
      :else -> special?(list, index+1, l, List.last(ls))
    end
  end

end
