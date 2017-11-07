defmodule Optimum do
  @moduledoc """
  https://projecteuler.net/problem=103
  """

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

  def solution() do
    for x1 <- 19..25,
      x2 <- 30..36,
      x3 <- 36..42,
      x4 <- 39..45,
      x5 <- 39..47,
      x6 <- 39..48,
      x7 <- 43..49,
      x7 > x6 and x6 > x5 and x5 > x4 and x4 > x3 and x3 > x2 and x2 > x1 do
	[x1, x2, x3, x4, x5, x6, x7]
    end
    |> Enum.filter(fn x -> x |> special? end)
    |> Enum.sort_by(fn x -> x |> Enum.sum() end)
    |> List.first()
  end
end
