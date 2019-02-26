defmodule Euler177 do
  @pi :math.pi()

  def get_cross_angle(a0, a1, a2, a3) do
    line0 = {:math.tan((90 - a0) / 180 * @pi), 0}
    line1 = {:math.tan((a1 + 90) / 180 * @pi), 0}
    line2 = {:math.tan((a2 + 90) / 180 * @pi), 1}
    line3 = {:math.tan((90 - a3) / 180 * @pi), 1}
    {x0, y0} = get_cross(line0, line2)
    {x1, y1} = get_cross(line1, line3)
    at = :math.atan((y1 - y0) / (x1 - x0)) / @pi * 180
    {90 - a3 - at, 90 - a1 + at, 90 - a2 + at, 90 - a0 - at}
  end

  # 计算两线交点
  defp get_cross({"∞", c1}, {k2, c2}), do: {c1, c1 * k2 + c2}
  defp get_cross({k2, c2}, {"∞", c1}), do: {c1, c1 * k2 + c2}

  defp get_cross({k1, c1}, {k2, c2}), do: {(c1 - c2) / (k2 - k1), (k1 * c2 - k2 * c1) / (k1 - k2)}

  def run() do
    for a0 <- 1..98,
        a1 <- 1..(98 - a0) do
      {a0, a1}
    end
    |> Enum.count()
  end
end
