defmodule CubeDigitPairs do
  @moduledoc """
  https://projecteuler.net/problem=90
  01, 04, 09, 16, 25, 36, 49, 64, 81

  (0, 1)   must be on 2 cubes
  (0, 4)   must be on 2 cubes
  (0, 6|9) must be on 2 cubes
  (1, 6|9) must be on 2 cubes
  (2, 5)   must be on 2 cubes
  (3, 6|9) must be on 2 cubes
  (4, 6|9) must be on 2 cubes
  (1, 8)   must be on 2 cubes
  """
  @elems [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

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

  def each_has({left, right}, a, "6|9") do
    cond do
      Enum.member?(left, a) and Enum.member?(right, 6) -> true
      Enum.member?(left, a) and Enum.member?(right, 9) -> true
      Enum.member?(left, 6) and Enum.member?(right, a) -> true
      Enum.member?(left, 9) and Enum.member?(right, a) -> true
      :else -> false
    end
  end
  def each_has({left, right}, a, b) do
    cond do
      Enum.member?(left, a) and Enum.member?(right, b) -> true
      Enum.member?(left, b) and Enum.member?(right, a) -> true
      :else -> false
    end
  end


  def solution() do
    left_cands = @elems |> choose(6)
    right_cands = @elems |> choose(6)
    all = for left <- left_cands,
      right <- right_cands do
	{left, right}
    end
    all |> Enum.filter(fn x -> each_has(x, 0, 1) end)
    |> Enum.filter(fn x -> each_has(x, 0, 4) end)
    |> Enum.filter(fn x -> each_has(x, 0, "6|9") end)
    |> Enum.filter(fn x -> each_has(x, 1, "6|9") end)
    |> Enum.filter(fn x -> each_has(x, 2, 5) end)
    |> Enum.filter(fn x -> each_has(x, 3, "6|9") end)
    |> Enum.filter(fn x -> each_has(x, 4, "6|9") end)
    |> Enum.filter(fn x -> each_has(x, 1, 8) end)
    |> length
    |> div(2)
  end
end
