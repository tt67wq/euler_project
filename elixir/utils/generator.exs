defmodule Generator do
  @moduledoc """
  排列组合算法的elixir实现
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

  @doc """
  ## Example
  
      iex> Generator.arrange([1, 2, 3])
      [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
  """
  @spec arrange(List) :: List
  def arrange(lst), do: arg(lst) |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end) |> MapSet.to_list()
  defp arg(lst) when length(lst) == 1, do: [lst]
  defp arg([h|t]), do: arrange(t) |> Enum.reduce([], fn x, acc -> insert(h, x) ++ acc end)
  defp insert(n, lst), do: 0..length(lst) |> Enum.map(fn x -> List.insert_at(lst, x, n) end)

  @doc """
  将list分割成2份可能性
  ## Example

      iex> list_split([1, 2, 3])
      [[[1, 2], [3]], [[1, 3], [2]], [[2, 3], [1]]]

  """
  def list_cut(list), do: lc(list, 1, [])
  defp lc(list, count, acc) when count * 2 > length(list), do: acc
  defp lc(list, count, acc) do
    nacc = acc ++ choose(list, count)
    |> Enum.map(fn x -> [x, list_sub(list, x)]
    |> Enum.sort end)
    |> MapSet.new()
    |> MapSet.to_list
    lc(list, count+1, nacc)
  end
  defp list_sub(list1, list2), do: list1 |> Enum.filter(fn x -> not Enum.member?(list2, x) end)


end
