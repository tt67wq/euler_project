defmodule PasscodeDerivation do
  @moduledoc """
  https://projecteuler.net/problem=79
  """
  require Logger
  @doc """
  判断一个list是否包含另外一个list
  ## Example

      iex> PasscodeDerivation.in_list?([1,3,5,7],[1,3,7])
      true
  """
  def in_list?(_, []), do: true
  def in_list?([], _), do: false
  def in_list?([h1|t1], [h2|t2]) when h1 == h2, do: in_list?(t1, t2)
  def in_list?([_|t], l), do: in_list?(t, l)

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
  按既有顺序合并两个list
  ## Example

      iex> PasscodeDerivation.merge_list([3,1,9],[6, 8, 0])
      [[6, 8, 0, 3, 1, 9], [6, 8, 3, 0, 1, 9], [6, 8, 3, 1, 0, 9], [6, 8, 3, 1, 9, 0],
      [6, 3, 8, 0, 1, 9], [6, 3, 8, 1, 0, 9], [6, 3, 8, 1, 9, 0], [6, 3, 1, 8, 0, 9],
      [6, 3, 1, 8, 9, 0], [6, 3, 1, 9, 8, 0], [3, 6, 8, 0, 1, 9], [3, 6, 8, 1, 0, 9],
      [3, 6, 8, 1, 9, 0], [3, 6, 1, 8, 0, 9], [3, 6, 1, 8, 9, 0], [3, 6, 1, 9, 8, 0],
      [3, 1, 6, 8, 0, 9], [3, 1, 6, 8, 9, 0], [3, 1, 6, 9, 8, 0], [3, 1, 9, 6, 8, 0]]
  """
  def merge_list(list1, list2) do
    l1 = length(list1)
    l2 = length(list2)
    elems = List.duplicate(1, l1) ++ List.duplicate(0, l2)
    |> arrange()
    |> Enum.map(fn x -> ml(list1, list2, x, []) end)
    |> Enum.map(fn x -> min_slice(x, list1, list2) |> Enum.dedup() end)
    |> Enum.uniq()

    min_len = elems |> Enum.map(fn x -> length(x) end)
    |> Enum.min()

    elems |> Enum.filter(fn x -> length(x) == min_len end)
  end

  defp ml(_, _, [], acc), do: Enum.reverse(acc)
  defp ml(l1, [h2|t2], [0|t3], acc), do: ml(l1, t2, t3, [h2|acc])
  defp ml([h1|t1], l2, [1|t3], acc), do: ml(t1, l2, t3, [h1|acc])

  # @doc """
  # 压缩一个list
  # ## Example

  #     iex> compress([6, 3, 1, 2, 8, 9, 9, 0])
  #     [6, 3, 1, 2, 8, 9, 0]
  # """
  # def compress(list), do: cp(list, 1, list)
  # defp cp([h1, h2|t], index, acc) do
    
  # end


  @doc """
  截取list中包含l1和l2的最小分片
  ## Example

      iex> min_slice([1, 9, 3, 1, 9, 2], [3, 1, 9], [1, 9, 2])
      [3, 1, 9, 2]
  """
  def min_slice(list, l1, l2), do: ms(list, l1, l2, list)
  defp ms([_h|t]=list, l1, l2, acc) do
    cond do
      in_list?(list, l1) and in_list?(list, l2) -> ms(t, l1, l2, list)
      :else -> acc
    end
  end

  # -------------------- solution --------------------

  def to_int_list(num), do: to_ilist(num, [])
  defp to_ilist(0, acc), do: acc
  defp to_ilist(num, acc), do: to_ilist(div(num, 10), [rem(num, 10) | acc])

  def solution() do
    {:ok, content} = File.read("p079_keylog.txt")
    [h|t] = content |> String.split("\n")
    |> Enum.filter(fn x -> x != "" end)
    |> Enum.map(fn x -> String.to_integer(x) end)
    |> Enum.map(fn x -> to_int_list(x) end)
    sl(t, [h])
  end

  def folder(list), do: fd(list, [])
  defp fd([], acc), do: acc
  defp fd([h|t], acc), do: fd(t, acc ++ h)

  defp sl([], acc), do: acc
  defp sl([h|t], acc) do
    Logger.info("dealing with: #{inspect h}")
    elems = acc |> Enum.filter(fn x -> in_list?(x, h) end)
    Logger.info("elems: #{inspect elems}")
    case length(elems) do
      0 -> sl(t, acc |> Enum.map(fn x -> merge_list(x, h) end) |> folder())
      _ -> sl(t, elems)
    end
  end
end
