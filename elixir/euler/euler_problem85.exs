defmodule CountingRectangles do
  @moduledoc """
  https://projecteuler.net/problem=85
  """
  def contains({l, w}, {x, y}), do: (l - x + 1) * (w - y + 1)

  def counting_rectangles(l, w) do
    for x <- 1..l,
      y <- 1..w do
	contains({l, w}, {x, y})
    end
    |> Enum.sum()
  end

  def ab(x) when x < 0, do: 0 - x
  def ab(x), do: x
  
  def solution() do
    for l <- 10..100,
    w <- 10..100 do
	{l, w, counting_rectangles(l, w)}
    end
    |> Enum.min_by(fn {_l, _w, c} -> ab(c - 2000000) end)
  end
end
