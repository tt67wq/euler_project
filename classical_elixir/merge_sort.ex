defmodule MergeSort do
  @moduledoc """
  归并排序的elixir实现
  """

  @doc """
  合并两个列表
  """
  @spec merge(list, list) :: list
  def merge(a, b), do: merge(a, b, [])
  defp merge([], [], acc), do: Enum.reverse(acc)
  defp merge(a, [], acc), do: Enum.reverse(acc) ++ a
  defp merge([], b, acc), do: Enum.reverse(acc) ++ b
  defp merge([h1 | _t1] = a, [h2 | t2], acc) when h1 > h2, do: merge(a, t2, [h2 | acc])
  defp merge([h1 | t1], b, acc), do: merge(t1, b, [h1 | acc])

  @doc """
  分割一个列表
  """
  @spec divide(list) :: tuple
  def divide(list), do: divide(list, length(list), 0, [], [])
  defp divide([], _l, _i, a, b), do: {a, b}

  defp divide([h | t], len, index, a, b) when index < div(len, 2),
    do: divide(t, len, index + 1, [h | a], b)

  defp divide([h | t], len, index, a, b), do: divide(t, len, index + 1, a, [h | b])

  @doc """
  归并排序
  """
  def mergeSort([x]), do: [x]

  def mergeSort(list) do
    {left, right} = divide(list)
    merge(mergeSort(left), mergeSort(right))
  end
end
