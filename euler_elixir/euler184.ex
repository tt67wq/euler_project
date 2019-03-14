defmodule Euler184 do
  @moduledoc """
  https://projecteuler.net/problem=184
  """

  # 判断原点是否在点a,b,c组成的三角形内部
  def inner_origin({ax, ay}, {bx, by}, {cx, cy}) do
    sign = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax)
    signAB = (bx - ax) * (0 - ay) - (by - ay) * (0 - ax)
    signCA = (ax - cx) * (0 - cy) - (ay - cy) * (0 - cx)
    signBC = (cx - bx) * (0 - cy) - (cy - by) * (0 - cx)

    false not in [signAB * sign > 0, signCA * sign > 0, signBC * sign > 0]
  end

  def test(n) do
    l = n - 1

    points =
      for x <- -l..l,
          y <- -l..l,
          x * x + y * y < n * n do
        {x, y}
      end

    for a <- points,
        b <- points,
        c <- points do
      [a, b, c] |> Enum.sort()
    end
    |> Enum.uniq()
    |> Enum.filter(fn [a, b, c] -> inner_origin(a, b, c) end)
    |> Enum.count()
  end
end
