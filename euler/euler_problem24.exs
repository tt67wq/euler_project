defmodule LexicographicPermutations do
  @moduledoc """
  https://projecteuler.net/problem=24
  """
  @doc """
  ## Example
  
      iex> Generator.arrange([1, 2, 3])
      [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
  """
  @spec arrange(List) :: List
  def arrange(lst) when length(lst) == 1, do: [lst]
  def arrange([h|t]), do: arrange(t) |> Enum.reduce([], fn x, acc -> insert(h, x) ++ acc end)
  def insert(n, lst), do: 0..length(lst) |> Enum.map(fn x -> List.insert_at(lst, x, n) end)

  @doc """
  列表转数字
  ## Example

      iex> Generator.list2number([1,2,3,4])
      1234
  """
  def list2number(lst), do: l2n(lst, 0)
  defp l2n([], acc), do: acc
  defp l2n([h|t], acc), do: l2n(t, acc * 10 + h)

  def solution() do
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9] |> arrange()
    |> Enum.map(fn x -> list2number(x) end)
    |> Enum.sort()
    |> Enum.at(1000001)
  end

end
