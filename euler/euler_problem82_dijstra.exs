defmodule PathSum do
  @moduledoc """
  https://projecteuler.net/problem=82
  """
  require Logger

  def to_int_list(list), do: list |> Enum.map(fn x -> String.to_integer(x) end)
  def solution() do
    {:ok, content} = File.read("p082_matrix.txt")
    list = content |> String.split("\n")
    |> Enum.filter(fn x -> x != "" end)
    |> Enum.map(fn x -> String.split(x, ",") end)
    |> Enum.map(fn x -> to_int_list(x) end)

    matrix = build_path_matrix(list)
    all = for y <- 0..79 do
      get_min_path(list, matrix, {0, y}) |> Enum.filter(fn {x, _, _, _} -> x == 79 end)
      |> Enum.map(fn x -> {x, y} end)
      |> Enum.min_by(fn {{_,_, x ,_}, _} -> x end)
    end
    all |> Enum.min_by(fn {{_,_, x ,_}, _} -> x end)
  end

  def get_min_path(list, matrix, {x, y}) do
    v = get_matrix_elem(list, x, y)
    acc = Map.fetch!(matrix, {x, y})
    |> Enum.filter(fn {_,_,v,_} -> v != nil end)
    |> Enum.map(fn {x, y, v1, :uncertain} -> {x, y, v1 + v, :uncertain} end)
    iter(matrix, acc)
  end

  def iter(om, acc) do
    target = get_nearest_uncertain(acc)
    case target do
      nil -> acc
      _ ->
	{x, y, v, _} = target
	nacc = acc |> upsert(target, {x, y, v, :certain})
	## 松弛
	lst = Map.fetch!(om, {x, y}) |> Enum.filter(fn {_, _, x, _} -> x != nil end)
	iter(om, slack(om, v, nacc, lst))
    end
  end

  defp slack(_om, _v, acc, []), do: acc
  defp slack(om, v, acc, [h|t]) do
    {x, y, v1, _} = h
    direct = get_distance(acc, x, y)
    sl = v + v1
    cond do
      direct < sl -> slack(om, v, acc, t)
      :else -> slack(om, v, upsert(acc, {x, y, direct, :uncertain}, {x, y, sl, :uncertain}), t)
    end
  end

  def get_distance([], _x, _y), do: 100000000000000000000
  def get_distance([h|t], x, y) do
    case h do
      {x1, y1, v, _} ->
	cond do
	  x1 == x and y1 == y -> v
	  :else -> get_distance(t, x, y)
	end
      _ -> get_distance(t, x, y)
    end
  end

  @doc """
  获得未确定的点中路径最短的
  """
  def get_nearest_uncertain(list) do
    ul = list |> Enum.filter(fn {_, _, _, x} -> x != :certain end)
    cond do
      ul |> length() > 0 -> ul |> Enum.min_by(fn {_, _, x, _} -> x end)
      :else -> nil
    end
  end

  def get_acc_elem([], _), do: nil
  def get_acc_elem([h|t], {x, y}) do
    {x1, y1, _, _} = h
    case {x1-x, y1-y} do
      {0, 0} -> h
      _ -> get_acc_elem(t, {x,y})
    end
  end

  @doc """
  获得方阵中指定坐标的值
  """
  def get_matrix_elem(_matrix, x, y) when x < 0 or y < 0, do: nil
  def get_matrix_elem(matrix, x, y) do
    case Enum.at(matrix, y) do
      nil -> nil
      _ -> Enum.at(matrix, y) |> Enum.at(x)
    end
  end

  def build_path_matrix(matrix) do
    l = length(matrix)
    # {bpm_out(matrix, l-1, 0, 0, %{}), bpm_in(matrix, l-1, 0, 0, %{})}
    bpm_out(matrix, l-1, 0, 0, %{})
  end

  def upsert(list, elem1, elem2), do: us(list, elem1, elem2, [])
  defp us([], _, elem, acc) do
    cond do
      Enum.member?(acc, elem) -> acc |> Enum.reverse
      :else -> [elem|acc] |> Enum.reverse
    end
  end
  defp us([h|t], h, n, acc), do: us(t, h, n, [n|acc])
  defp us([h|t], o, n, acc), do: us(t, o, n, [h|acc])

  def path_add(_, nil), do: nil
  def path_add(nil, _), do: nil
  def path_add(a, b), do: a + b
  
  defp bpm_out(_matrix, l, l, y, state) when y > l, do: state
  defp bpm_out(matrix, l, x, y, state) when x > l, do: bpm_out(matrix, l, 0, y + 1, state)
  defp bpm_out(matrix, l, x, y, state) do
    up = matrix |> get_matrix_elem(x, y - 1)
    right = matrix |> get_matrix_elem(x + 1, y)
    down  = matrix |> get_matrix_elem(x, y + 1)
    bpm_out(matrix, l, x+1, y, state |> Map.put({x, y}, [{x + 1, y, right, :uncertain}, {x, y + 1, down, :uncertain}, {x, y - 1, up, :uncertain}]))
  end
end
