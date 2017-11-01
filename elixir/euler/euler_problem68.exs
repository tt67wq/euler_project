defmodule Magic5gonRing do
  @moduledoc """
  https://projecteuler.net/problem=68
  """
  @doc """

  ## Example
  
      iex>?> Generator.arrange([1, 2, 3])
      [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
  """
  @spec arrange(List) :: List
  def arrange(lst) when length(lst) == 1, do: [lst]
  def arrange([h|t]), do: arrange(t) |> Enum.reduce([], fn x, acc -> insert(h, x) ++ acc end)
  def insert(n, lst), do: 0..length(lst) |> Enum.map(fn x -> List.insert_at(lst, x, n) end)


  @doc """
  检测外圈与内圈是否按条件匹配
  """
  def satisfy(out_line, [h|_]=inner_line), do: sfy(out_line, inner_line ++ [h], 0)
  defp sfy([], _, _), do: true
  defp sfy([h|t], [h1, h2|t1], 0), do: sfy(t, [h2|t1], h + h1 + h2)
  defp sfy([h|t], [h1, h2|t1], acc) do
    cond do
      h + h1 + h2 == acc -> sfy(t, [h2|t1], acc)
      :else -> false
    end
  end

  def get_number(out_line, [h|_]=inner_line), do: gn(out_line, inner_line ++ [h], [])
  defp gn([], _, acc), do: acc |> Enum.reverse() |> list2number()
  defp gn([h|t], [h1, h2|t1], acc), do: gn(t, [h2|t1], [list2number([h, h1, h2]) | acc])

  def list2number(lst), do: l2n(lst |> Enum.reverse(), 0)
  defp l2n([], acc), do: acc
  defp l2n([h|t], 0), do: l2n(t, h)
  defp l2n([h|t], acc) do
    c = acc |> to_charlist() |> length()
    l2n(t, h * (:math.pow(10, c) |> round()) + acc)
  end


  def solution() do
    out_line_list = arrange([6, 7, 8, 9, 10])
    innner_line_list = arrange([1, 2, 3, 4, 5])
    solution(out_line_list, innner_line_list, []) |> Enum.map(fn [o, i] -> get_number(o, i) end) |> Enum.max()
  end

  defp solution(olist, ilist, acc) do
    for o <- olist,
      i <- ilist,
      satisfy(o, i),
      Enum.at(o, 0) == Enum.min(o) # 取最小开头的，因为其他的排序都是旋转等效的
      do
      [o, i | acc]
    end

  end
end
