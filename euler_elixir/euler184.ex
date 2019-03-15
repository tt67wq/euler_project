defmodule Euler184 do
  @moduledoc """
  https://projecteuler.net/problem=184
  """
  require Integer

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
  end

  def test(n) do
    points = get_points(n)

    group_points(points, %{})
    # mp = group_points(points, %{})
    # base_ps = Map.keys(mp)

    # for a <- base_ps,
    #     b <- base_ps,
    #     c <- base_ps do
    #   {a, b, c}
    # end
    # |> Enum.uniq_by(fn {a, b, c} -> Enum.sort([a, b, c]) end)
    # |> Enum.filter(fn {a, b, c} -> inner_origin(a, b, c) end)
    # |> Enum.map(fn {a, b, c} -> Map.fetch!(mp, a) * Map.fetch!(mp, b) * Map.fetch!(mp, c) end)
    # |> Enum.sum
  end

  defp group_points([], acc), do: acc
  defp group_points([{0, 0} | t], acc), do: group_points(t, acc)

  defp group_points([{0, y} | t], acc) do
    k =
      cond do
        y > 0 -> {0, 1}
        :else -> {0, -1}
      end

    group_points(t, Map.update(acc, k, 1, fn z -> z + 1 end))
  end

  defp group_points([{x, 0} | t], acc) do
    k =
      cond do
        x > 0 -> {1, 0}
        :else -> {-1, 0}
      end

    group_points(t, Map.update(acc, k, 1, fn z -> z + 1 end))
  end

  defp group_points([{x, y} | t], acc) do
    g = Integer.gcd(x, y)
    k = {div(x, g), div(y, g)}
    group_points(t, Map.update(acc, k, 1, fn z -> z + 1 end))
  end
end
