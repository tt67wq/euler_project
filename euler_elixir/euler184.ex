defmodule Euler184 do
  @moduledoc """
  https://projecteuler.net/problem=184
  """
  require Integer
  require Logger

  # 判断原点是否在点a,b,c组成的三角形内部
  def inner_origin({ax, ay}, {bx, by}, {cx, cy}) do
    sign = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax)
    signAB = (bx - ax) * (0 - ay) - (by - ay) * (0 - ax)
    signCA = (ax - cx) * (0 - cy) - (ay - cy) * (0 - cx)
    signBC = (cx - bx) * (0 - cy) - (cy - by) * (0 - cx)

    false not in [signAB * sign > 0, signCA * sign > 0, signBC * sign > 0]
  end

  def get_points(n) do
    l = n - 1

    for x <- -l..l,
        y <- -l..l,
        x * x + y * y < n * n do
      {x, y}
    end
    |> Enum.filter(fn x -> x != {0, 0} end)
  end

  # 向量差积
  def vector_cross({x1, y1}, {x2, y2}), do: x1 * y2 - x2 * y1

  def test(n) do
    points = get_points(n)

    pnum = Enum.count(points)
    p1 = around_point(points, points, 0)

    gp = group_points(points, %{})
    Logger.info("#{inspect(gp)}")
    # group_points(points, %{})
    p2 =
      gp
      |> Map.values()
      |> Enum.map(fn x -> div(x, 2) * div(x, 2) * (pnum - x) + div(x * (x - 1) * (x - 2), 6) end)
      |> Enum.sum()

    Logger.info("#{p1}, #{p2}")

    div(pnum * (pnum - 1) * (pnum - 2), 6) - div(p1, 2) - p2
  end

  defp around_point([], _, acc), do: acc

  defp around_point([h | t], ps, acc) do
    n =
      Enum.filter(ps, fn x -> vector_cross(x, h) < 0 end)
      |> Enum.count()

    around_point(t, ps, acc + n * (n - 1))
  end

  defp group_points([], acc), do: acc

  defp group_points([{0, _} | t], acc),
    do: group_points(t, Map.update(acc, {0, 1}, 1, fn z -> z + 1 end))

  defp group_points([{_, 0} | t], acc),
    do: group_points(t, Map.update(acc, {1, 0}, 1, fn z -> z + 1 end))

  defp group_points([{x, y} | t], acc) do
    g = Integer.gcd(x, y)
    gx = div(x, g)
    gy = div(y, g)

    k =
      cond do
        gx > 0 and gy > 0 -> {gx, gy}
        gx < 0 and gy > 0 -> {gx, gy}
        gx > 0 and gy < 0 -> {-gx, -gy}
        gx < 0 and gy < 0 -> {-gx, -gy}
      end

    group_points(t, Map.update(acc, k, 1, fn z -> z + 1 end))
  end
end
