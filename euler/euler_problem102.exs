defmodule TriangleContainment do
  @moduledoc """
  https://projecteuler.net/problem=102
  """
  require Logger

  def solution() do
    {_, content} = File.read("p102_triangles.txt")
    content |> String.split("\n")
    |> Enum.filter(fn x -> x != "" end)
    |> Enum.map(fn x -> x |> String.split(",") end)
    |> Enum.map(fn x -> x |> slist2ilist end)
    |> Enum.filter(fn x -> x |> contain_origin? end)
  end

  def slist2ilist(list), do: list |> Enum.map(fn x -> x |> String.to_integer() end)

  def get_k({x1, _}, {x2, _}) when x1 == x2, do: nil
  def get_k({x1, y1}, {x2, y2}), do: (y2 - y1) / (x2 - x1)

  defp get_b(x, y, k), do: y - k * x

  def get_side({x1, y1}, {x2, y2}) do
    a = x2 - x1
    b = y2 - y1
    cond do
      a > 0 and b > 0 ->
	k = get_k({x1, y1}, {x2, y2})
	b = get_b(x1, y1, k)
	cond do
	  b > 0 -> :right
	  b < 0 -> :left
	end
      a > 0 and b < 0 ->
	k = get_k({x1, y1}, {x2, y2})
	b = get_b(x1, y1, k)
	cond do
	  b > 0 -> :right
	  b < 0 -> :left
	end
      a < 0 and b > 0 ->
	k = get_k({x1, y1}, {x2, y2})
	b = get_b(x1, y1, k)
	cond do
	  b > 0 -> :left
	  b < 0 -> :right
	end
      a < 0 and b < 0 ->
	k = get_k({x1, y1}, {x2, y2})
	b = get_b(x1, y1, k)
	cond do
	  b > 0 -> :left
	  b < 0 -> :right
	end
      a == 0 and b > 0 ->
	cond do
	  x1 > 0 -> :left
	  x1 < 0 -> :right
	end
      a == 0 and b < 0 ->
	cond do
	  x1 > 0 -> :right
	  x1 < 0 -> :left
	end
      a > 0 and b == 0 ->
	cond do
	  y1 > 0 -> :right
	  y1 < 0 -> :left
	end
      a < 0 and b == 0 ->
	cond do
	  y1 > 0 -> :left
	  y1 < 0 -> :right
	end
      :else -> Logger.info("#{inspect {x1, y1}}, #{inspect {x2, y2}}")
    end
  end

  def contain_origin?([x1, y1, x2, y2, x3, y3]) do
    side1 = get_side({x1, y1}, {x2, y2})
    side2 = get_side({x2, y2}, {x3, y3})
    side3 = get_side({x3, y3}, {x1, y1})
    MapSet.new([side1, side2, side3]) |> MapSet.size() == 1
  end
end
