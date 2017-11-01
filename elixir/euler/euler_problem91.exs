defmodule RightTrianglesWithIntegerCoordinates do
  @moduledoc """
  https://projecteuler.net/problem=91
  """

  @limit 50

  def triangle?(_, {0, 0}), do: false
  def triangle?({0, 0}, _), do: false
  def triangle?({x1, y1}, {x2, y2}) when x1 == x2 and y1 == y2, do: false
  def triangle?({0, _}, {_, 0}), do: true
  def triangle?({_, 0}, {0, _}), do: true
  def triangle?({x1, y1}, {x2, y2}) do
    t = x1 * x2 + y1 * y2
    cond do
      t == x1 * x1 + y1 * y1 -> true
      t == x2 * x2 + y2 * y2 -> true
      :else -> false
    end
  end

  def solution() do
    for x1 <- 0..@limit,
      y1 <- 0..@limit,
      x2 <- 0..@limit,
      y2 <- 0..@limit,
      triangle?({x1, y1}, {x2, y2}) do
	{{x1, y1}, {x2, y2}}
    end
    |> length
    |> div(2)
  end
end
