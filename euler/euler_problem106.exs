defmodule MetaTesting do
  @moduledoc """
  https://projecteuler.net/problem=106
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

  def get_subset_pairs(list), do: gsp(list, 1, 1, [])
  defp gsp(list, a, 1, acc) when a > length(list), do: acc
  defp gsp(list, a, b, acc) when length(list) < a+b, do: gsp(list, a+1, 1, acc)
  defp gsp(list, a, b, acc) when b > a, do: gsp(list, a+1, 1, acc)
  defp gsp(list, a, b, acc) do
    Logger.info("#{a}, #{b}")
    cs = for x <- choose(list, a),
      y <- choose(list |> Enum.filter(fn t -> not Enum.member?(x, t) end), b) do
	[x, y] |> Enum.sort()
    end
    |> MapSet.new()
    |> MapSet.to_list()
    gsp(list, a, b+1, acc ++ cs)
  end

  def need_to_compare?(list1, list2) do
    cond do
      length(list1) != length(list2) -> false
      one_side?(list1, list2) -> false
      :else -> true
    end
  end

  def one_side?([h1|t1], [h2|t2]) do
    cond do
      h1 > h2 -> ones(t1, t2, :bigger)
      :else -> ones(t1, t2, :smaller)
    end
  end

  defp ones([], [], _), do: true
  defp ones([h1|t1], [h2|t2], :bigger) do
    cond do
      h1 > h2 -> ones(t1, t2, :bigger)
      :else -> false
    end
  end
  defp ones([h1|t1], [h2|t2], :smaller) do
    cond do
      h1 < h2 -> ones(t1, t2, :smaller)
      :else -> false
    end
  end

  def solution() do
    get_subset_pairs(1..12 |> Enum.to_list)
    |> Enum.filter(fn [x1, y1] -> need_to_compare?(x1, y1) end)
    |> length
  end
end
