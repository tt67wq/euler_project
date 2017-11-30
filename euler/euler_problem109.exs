defmodule Darts do
  @moduledoc """
  https://projecteuler.net/problem=109
  """
  # 一次投标的所有结果
  def one_dart_results() do
    rs = for m <- 1..3,
      n <- 1..20 do
	{m, n}
    end
    [{0, 0}, {1, 25}, {2, 25}|rs]
  end

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

  def get_combine([]), do: []
  def get_combine(list) do
    {d, _} = list |> List.last()
    cond do
      d != 2 -> []
      :else ->
	case length(list) do
	  3 ->
	    [m1, m2, m3] = list
	    ([m1, m2] |> Enum.sort) ++ [m3]
	  _ -> list
	end
    end
  end


  def solution() do
    rs = one_dart_results()
    mp = for {m1, n1} <- rs,
      {m2, n2} <- rs,
    {m3, n3} <- rs do
	point = m1 * n1 + m2 * n2 + m3 * n3
	combine = [{m1, n1}, {m2, n2}, {m3, n3}] |> Enum.filter(fn x -> x != {0, 0} end) |> get_combine
	{point, combine}
    end
    |> Enum.filter(fn {_, x} -> x != [] end)
    |> Enum.reduce(%{}, fn {p, y}, acc ->  Map.update(acc, p, [y], fn x -> [y|x] end) end)

    ks = mp |> Map.keys |> Enum.filter(fn x -> x < 100 end)
    ks |> Enum.map(fn x -> {x, Map.fetch!(mp, x)} end)
    |> Enum.map(fn {y, x} -> {y, x |> Enum.sort |> Enum.dedup} end)
    |> Enum.map(fn {_, x} -> x |> length end)
    |> Enum.sum
  end
  
end
