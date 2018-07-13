defmodule MinimalNetwork do
  @moduledoc """
  https://projecteuler.net/problem=107
  """
  require Integer
  require Logger
  
  def solution() do
    {:ok, content} = File.read("p107_network.txt")
    matrix = content |> String.split("\n")
    |> Enum.filter(fn x -> x != "" end)
    |> Enum.map(fn x -> x |> String.split(",") end)
    |> Enum.map(fn x -> x |> strings2ints end)
    # matrix = @example
    weight = matrix |> Enum.map(fn x -> x |> Enum.sum end) |> Enum.sum |> div(2)
    Logger.info(weight)
    map = matrix |> build_map
    # Logger.info("#{inspect map}")
    md = walk(map)
    Logger.info(md)
    weight - md
  end

  defp walk(map), do: walk(map, 0, ["p1"], map |> Map.keys |> length)
  defp walk(_map, l, acc, ml) when length(acc) == ml, do: l
  defp walk(map, l, acc, ml) do
    {np, d} = acc |> Enum.reduce([], fn x, bcc -> Map.fetch!(map, x) ++ bcc end)
    |> Enum.filter(fn {x, _} -> not Enum.member?(acc, x) end)
    |> Enum.min_by(fn {_, x} -> x end)
    walk(map, l + d, [np|acc], ml)
  end

  def strings2ints(list), do: s2i(list, [])
  defp s2i([], acc), do: acc |> Enum.reverse
  defp s2i(["-"|t], acc), do: s2i(t, [0|acc])
  defp s2i([h|t], acc), do: s2i(t, [h |> String.to_integer|acc])

  def build_map(list), do: bm(list, 1, %{})
  defp bm([], _, acc), do: acc
  defp bm([h|t], index, acc) do
    key = "p" <> (index |> Integer.to_string)
    bm(t, index+1, Map.update(acc, key, get_connected_point_info(h), &(&1)))
  end

  def get_connected_point_info(list), do: getcp(list, 1, [])
  defp getcp([], _, acc), do: acc
  defp getcp([0|t], index, acc), do: getcp(t, index+1, acc)
  defp getcp([h|t], index, acc) do
    key = "p" <> (index |> Integer.to_string)
    getcp(t, index+1, [{key, h}|acc])
  end
end
