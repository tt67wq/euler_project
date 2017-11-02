defmodule SuDoku do
  @moduledoc """
  https://projecteuler.net/problem=96
  """
  require Logger
  @basic MapSet.new([1,2,3,4,5,6,7,8,9])

  def pop_head_and_blank(list) do
    [_|t] = list
    t |> Enum.filter(fn x -> x != "" end)
  end

  def strings2ints(s) do
    0..8 |> Enum.map(fn x -> s |> String.at(x) |> String.to_integer() end)
  end

  def get_elem(matrix, x, y), do: matrix |> Enum.at(y) |> Enum.at(x)

  def replace0(list), do: rp(list, [])
  defp rp([], acc), do: acc |> Enum.reverse
  defp rp([0|t], acc), do: rp(t, [@basic|acc])
  defp rp([h|t], acc), do: rp(t, [h|acc])

  def add_candidates(matrix), do: matrix |> Enum.map(fn x -> x |> replace0() end)

  def clear_line(list) do
    fixed = list |> Enum.filter(fn x -> x |> is_integer end) |> MapSet.new()
    cl(list, fixed, [])
  end
  defp cl([], _, acc), do: acc |> Enum.reverse
  defp cl([h|t], f, acc) do
    cond do
      is_integer(h) -> cl(t, f, [h|acc])
      :else -> cl(t, f, [MapSet.difference(h, f)|acc])
    end
  end

  def spin(matrix), do: spin(matrix, 0, [])
  defp spin(_matrix, 9, acc), do: acc |> Enum.reverse
  defp spin(matrix, x, acc), do: spin(matrix, x+1, [0..8 |> Enum.map(fn y -> get_elem(matrix, x, y) end)|acc])

  def split3([x1, x2, x3, x4, x5, x6, x7, x8, x9]), do: [[x1, x2, x3], [x4, x5, x6], [x7, x8, x9]]
  
  def grads_spin(matrix) do
    [[a1, b1, c1], [a2, b2, c2], [a3, b3, c3],
     [a4, b4, c4], [a5, b5, c5], [a6, b6, c6],
     [a7, b7, c7], [a8, b8, c8], [a9, b9, c9]] = matrix |> Enum.map(fn x -> x |> split3 end)
    [a1 ++ a2 ++ a3, b1 ++ b2 ++ b3, c1 ++ c2 ++ c3,
     a4 ++ a5 ++ a6, b4 ++ b5 ++ b6, c4 ++ c5 ++ c6,
     a7 ++ a8 ++ a9, b7 ++ b8 ++ b9, c7 ++ c8 ++ c9]
  end

  def fix(list), do: fix(list, [])
  defp fix([], acc), do: acc |> Enum.reverse
  defp fix([h|t], acc) do
    cond do
      is_integer(h) -> fix(t, [h|acc])
      :else ->
	case MapSet.size(h) do
	  1 -> fix(t, [h |> MapSet.to_list |> List.first | acc])
	  _ -> fix(t, [h|acc])
	end
    end
  end

  def iter(matrix) do
    matrix |> Enum.map(fn x -> clear_line(x) end) |> fix_once_appear_elem()
    |> spin() |> Enum.map(fn x -> clear_line(x) end) |> fix_once_appear_elem() |> spin()
    |> grads_spin() |> Enum.map(fn x -> clear_line(x) end) |> fix_once_appear_elem() |> grads_spin()
    |> Enum.map(fn x -> x |> fix() end)
  end

  def fix_only_one(list) do
    list |> Enum.filter(fn x -> not (x |> is_integer) end) |> Enum.reduce([], fn x, acc -> (x |> MapSet.to_list()) ++ acc end)
    |> get_once_appear_elem()
    |> Enum.reduce(list, fn x, acc -> fix_num(acc, x) end)
  end

  def list2map(lst), do: list2map(lst, %{})
  defp list2map([], acc), do: acc
  defp list2map([h|t], acc) do
    case Map.fetch(acc, h) do
      {:ok, c} -> list2map(t, Map.update(acc, h, c, &(&1 + 1)))
      :error -> list2map(t, Map.update(acc, h, 1, &(&1 + 1)))
    end
  end

  def get_once_appear_elem(list) do
    m = list |> list2map()
    m |> Map.keys() |> Enum.filter(fn x -> Map.fetch!(m, x) == 1 end)
  end

  def fix_num(list, num), do: fixn(list, num, [])
  defp fixn([], _, acc), do: acc |> Enum.reverse
  defp fixn([h|t], num, acc) do
    cond do
      is_integer(h) -> fixn(t, num, [h|acc])
      :else ->
	cond do
	  MapSet.member?(h, num) -> ([num|acc] |> Enum.reverse) ++ t
	  :else -> fixn(t, num, [h|acc])
	end
    end
  end

  def fix_once_appear_elem(matrix), do: matrix |> Enum.map(fn x -> x |> fix_only_one() end)

  def fixed?([]), do: true
  def fixed?([h|t]) do
    cond do
      is_integer(h) -> fixed?(t)
      :else -> false
    end
  end

  def all_fixed?(matrix) do
    matrix |> Enum.filter(fn x -> x |> fixed?() end)
    |> length == 9
  end

  def try_fix(list) do
    num = list |> Enum.filter(fn x -> not (x |> is_integer) end) |> Enum.random() |> MapSet.to_list() |> Enum.random()
    fix_num(list, num)
  end

  
  def try_iter(matrix) do
    index = [0,1,2,3,4,5,6,7,8] |> Enum.random()
    h = matrix |> Enum.at(index)
    List.replace_at(matrix, index, try_fix(h))
  end

  def get_nums(matrix) do
    [h1, h2, h3|_] = matrix |> List.first()
    h1 * 100 + h2 * 10 + h3
  end

  def check(matrix) do
    a = matrix |> Enum.map(fn x -> x |> MapSet.new() end) |> Enum.filter(fn x -> MapSet.equal?(x, @basic) end) |> length
    b = matrix |> spin() |> Enum.map(fn x -> x |> MapSet.new() end) |> Enum.filter(fn x -> MapSet.equal?(x, @basic) end) |> length
    c = matrix |> grads_spin() |> Enum.map(fn x -> x |> MapSet.new() end) |> Enum.filter(fn x -> MapSet.equal?(x, @basic) end) |> length
    a == 9 and b == 9 and c == 9
  end

  
  def solution() do
    {_, content} = File.read("p096_sudoku.txt")
    matrixes = content |> String.split(~r{Grid })
    |> Enum.filter(fn x -> x != "" end)
    |> Enum.map(fn x -> x |> String.split("\n") end)
    |> Enum.map(fn x -> x |> pop_head_and_blank() end)
    |> Enum.map(fn x -> x |> Enum.map(fn x -> x |> strings2ints() end) end)
    all = matrixes |> Enum.map(fn x -> add_candidates(x) end)
    |> Enum.map(fn x -> x |> solve_matrix() end)
    # [_, _, _, _,_, h|_] = all
    # h
    a = all |> Enum.filter(fn x -> not (x |> all_fixed?) end)
    |> Enum.map(fn x -> x |> try_solve() end)
    b = all |> Enum.filter(fn x -> x |> all_fixed? end)
    a ++ b
    |> Enum.map(fn x -> x |> get_nums() end)
  end

  def try_solve(matrix) do
    nm = matrix |> try_iter()
    nnm = nm |> solve_matrix()
    cond do
      all_fixed?(nnm) and check(nnm) -> nnm
      :else -> try_solve(matrix)
    end
  end

  def solve_matrix(matrix) do
    nm = matrix |> iter()
    cond do
      nm == matrix -> nm
      all_fixed?(nm) -> nm
      :else -> solve_matrix(nm)
    end
  end
end
