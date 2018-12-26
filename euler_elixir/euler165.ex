defmodule Euler165 do
  @moduledoc """
  https://projecteuler.net/problem=165
  """

  @limit 0.005

  def bbShub(n), do: bbs(n, 0, 290_797, [])
  defp bbs(n, index, _, acc) when index > n, do: Enum.reverse(acc) |> Enum.slice(1..-1)

  defp bbs(n, index, sn, acc),
    do: bbs(n, index + 1, rem(sn * sn, 50_515_093), [rem(sn, 500) | acc])

  def gene_line(nums), do: gl(nums, [])
  defp gl([], acc), do: acc

  defp gl([t1, t2, t3, t4 | t], acc) do
    cond do
      t1 < t3 ->
        gl(t, [{{t1, t2}, {t3, t4}} | acc])

      :else ->
        gl(t, [{{t3, t4}, {t1, t2}} | acc])
    end
  end

  # 计算两线交点
  def get_cross({"∞", b1}, {k2, b2}), do: {b1, b1 * k2 + b2}
  def get_cross({k2, b2}, {"∞", b1}), do: {b1, b1 * k2 + b2}

  def get_cross({k1, b1}, {k2, b2}), do: {(b1 - b2) / (k2 - k1), (k1 * b2 - k2 * b1) / (k1 - k2)}

  defp almost_equal(a, b), do: abs(a - b) <= @limit
  def almost_equal_point({a1, b1}, {a2, b2}), do: almost_equal(a1, a2) and almost_equal(b1, b2)

  # 判断两点是否real 相交
  def real_cross?({{x1, y1}, {x2, y2}}, {{x1, y1}, {x2, y2}}), do: false
  # 这里默认 x1 < x2, x3 < x4
  def real_cross?({{x1, y1}, {x2, y2}}, {{x3, y3}, {x4, y4}}) do
    k1 =
      case x2 - x1 do
        0 -> "∞"
        _ -> (y2 - y1) / (x2 - x1)
      end

    k2 =
      case x4 - x3 do
        0 -> "∞"
        _ -> (y4 - y3) / (x4 - x3)
      end

    cond do
      k1 == k2 ->
        false

      :else ->
        b1 =
          case k1 do
            "∞" -> x1
            _ -> (x2 * y1 - x1 * y2) / (x2 - x1)
          end

        b2 =
          case k2 do
            "∞" -> x3
            _ -> (x4 * y3 - x3 * y4) / (x4 - x3)
          end

        {x5, y5} = get_cross({k1, b1}, {k2, b2})

        cond do
          almost_equal_point({x5, y5}, {x1, y1}) ->
            false

          almost_equal_point({x5, y5}, {x2, y2}) ->
            false

          almost_equal_point({x5, y5}, {x3, y3}) ->
            false

          almost_equal_point({x5, y5}, {x4, y4}) ->
            false

          x5 < x1 or x5 > x2 ->
            false

          x5 < x3 or x5 > x4 ->
            false

          :else ->
            cond do
              k1 == "∞" and y5 > max(y1, y2) -> false
              k2 == "∞" and y5 > max(y3, y4) -> false
              k1 == "∞" and y5 < min(y1, y2) -> false
              k2 == "∞" and y5 < min(y3, y4) -> false
              :else -> true
            end
        end
    end
  end

  def run() do
    lines =
      bbShub(20000)
      |> gene_line()

    for l1 <- lines,
        l2 <- lines,
        l1 != l2 do
      [l1, l2]
    end
    # |> Enum.uniq()
    |> Enum.filter(fn [l1, l2] -> real_cross?(l1, l2) end)
    |> Enum.count()
    |> div(2)
  end
end
