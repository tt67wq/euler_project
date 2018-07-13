defmodule Optimum do
  @moduledoc """
  https://projecteuler.net/problem=103
  """

  require Logger

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

  def add_wide(list), do: aw(list, [])
  defp aw([], acc), do: acc |> Enum.reverse
  defp aw([h|t], acc), do: aw(t, [[h-2, h-1, h, h+1, h+2]|acc])

  def wide_adjust(list, wide), do: wa(list, wide, [])
  defp wa([], [], acc), do: acc |> Enum.reverse
  defp wa([h|t], [h1|t1], acc) do
    cond do
      h == List.first(h1) -> wa(t, t1, [h1 |> Enum.map(fn x -> x - 2 end)|acc])
	h == List.last(h1) -> wa(t, t1, [h1 |> Enum.map(fn x -> x + 2 end)|acc])
      :else -> wa(t, t1, [h1|acc])
    end
  end

  
  def sl([x1, x2, x3, x4, x5, x6, x7]=w) do
    a = for y1 <- x1,
      y2 <- x2,
      y3 <- x3,
      y4 <- x4,
      y5 <- x5,
      y6 <- x6,
      y7 <- x7,
      y7 > y6 and y6 > y5 and y5 > y4 and y4 > y3 and y3 > y2 do
	[y1, y2, y3, y4, y5, y6, y7]
    end
    |> Enum.filter(fn x -> x |> special? end)
    |> Enum.sort_by(fn x -> x |> Enum.sum end)
    |> List.first()
    nw = wide_adjust(a, w)
    Logger.info("#{inspect nw |> Enum.map(fn x -> x |> List.to_tuple end)}")
    cond do
      nw == w -> a
      :else -> sl(nw)
    end
  end
  
  def solution() do
    base = [22, 33, 39, 42, 44, 45, 46]
    wide = base |> add_wide
    # Logger.info("#{inspect wide |> Enum.map(fn x -> x |> List.to_tuple end)}")
    wide |> sl()
  end
end
