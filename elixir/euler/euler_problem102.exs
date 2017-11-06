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
    |> Enum.filter(fn x -> not (x |> contain_origin?) end)
    # |> length
  end

  def slist2ilist(list), do: list |> Enum.map(fn x -> x |> String.to_integer() end)

  def get_k([x1, _], [x2, _]) when x1 == x2, do: nil
  def get_k([x1, y1], [x2, y2]), do: (y2 - y1) / (x2 - x1)

  defp get_y_cross(x, y, k), do: y - k * x
  defp get_x_cross(k, yc), do: 0 - (yc / k)

  def get_cross([x1, y1], [x2, y2]) do
    k = get_k([x1, y1], [x2, y2])
    # Logger.info(k)
    case k do
      0.0 ->
	Logger.info("#{inspect [x1, y1]}, #{inspect [x2, y2]}")
	[{nil, 0}, {0, y1}]
      nil ->
	Logger.info("#{inspect [x1, y1]}, #{inspect [x2, y2]}")
	[{x1, 0}, {0, nil}]
      _ ->
	b = get_y_cross(x1, y1, k)
	[get_x_cross(k, b), b]
    end
  end

  
  def get_quadrant(nil, yc) do
    cond do
      yc > 0 -> ["c", "d"]
      yc < 0 -> ["a", "b"]
      :else -> ["a", "b", "c", "d"]
    end
  end

  def get_quadrant(xc, nil) do
    cond do
      xc > 0 -> ["b", "c"]
      xc < 0 -> ["a", "d"]
      :else -> ["a", "b", "c", "d"]
    end
  end

  def get_quadrant(xc, yc) do
    cond do
      xc > 0 and yc > 0 -> ["c"]
      xc > 0 and yc < 0 -> ["b"]
      xc < 0 and yc > 0 -> ["d"]
      xc < 0 and yc < 0 -> ["a"]
      :else -> ["a", "b", "c", "d"]
    end
  end

  def get_quadrant_of_point(x, y) do
    cond do
      x > 0 and y > 0 -> "a"
      x > 0 and y < 0 -> "d"
      x < 0 and y > 0 -> "b"
      x < 0 and y < 0 -> "c"
    end
  end

  def contain_origin?([x1, y1, x2, y2, x3, y3]) do
    [xc, yc] = get_cross([x1, y1], [x2, y2])
    Enum.member?(get_quadrant(xc, yc), get_quadrant_of_point(x3, y3))
    # Logger.info("#{inspect [x1, y1, x2, y2, x3, y3]}, #{xc}, #{yc}: #{contain}")
    # contain
  end
end
