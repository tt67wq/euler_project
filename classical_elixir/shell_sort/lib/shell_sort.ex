defmodule ShellSort do
  @moduledoc """
  希尔排序的elixir实现
  """

  @doc """
  Hello world.

  ## Examples

      iex> ShellSort.hello
      :world

  """
  def hello do
    :world
  end

  require Logger

  @doc """
  插入排序
  """
  def insertSort(list), do: insertSort(list, [])
  defp insertSort([], acc), do: acc
  defp insertSort([h|t], acc), do: insertSort(t, insert(h, acc))
  defp insert(x, [h|t]) when x > h, do: [h | insert(x, t)]
  defp insert(x, acc), do: [x|acc]

  def groupSort(list), do: groupSort(list, [])
  defp groupSort([], acc), do: acc
  defp groupSort([h|t], acc), do: groupSort(t, [insertSort(h)|acc])

  @doc """
  希尔排序
  """
  def shellSort(list), do: shellSort(list, div(length(list), 2))
  defp shellSort(list, 0) do
    tmp = insertSort(list)
    show(tmp)
    tmp
  end
  defp shellSort(list, gap) do
    tmp = list |> divide(gap) |> combine
    show(tmp)
    shellSort(tmp, div(gap, 2))
  end


  @doc """
  分组
  """
  def divide(list, x), do: divide(list, x, 1, %{})
  defp divide([], _x, _index, acc), do: groupSort(Map.values(acc))
  defp divide([h|t], x, index, acc) do
    k = rem(index, x)
    divide(t, x, index+1, Map.update(acc, k, [h], fn a -> [h|a] end))
  end

  def first(list), do: first(list, [], [])
  defp first([], acc1, acc2), do: {acc1, acc2}
  defp first([h|t], acc1, acc2) do
    case h do
      [] -> first(t, acc1, acc2)
      _ ->
	[h1|t1] = h
	first(t, [h1|acc1], [t1|acc2])
    end
  end

  @doc """
  将分组的再组合
  """
  def combine(list), do: combine(list, [])
  defp combine(list, acc) do
    {h, t} = first(list)
    cond do
      t == [] -> acc
      true -> combine(t, acc ++ h)
    end
  end

  @doc """
  打印出当前排列的进度
  """
  def show([]) do
    Logger.info("=============================")
    :timer.sleep(1000)
  end
  def show([h|t]) do
    Logger.info(String.duplicate("*", h))
    show(t)
  end
end
