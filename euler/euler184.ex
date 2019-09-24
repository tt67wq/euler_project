defmodule Euler184 do
  @moduledoc """
  https://projecteuler.net/problem=184
  """
  require Integer
  require Logger

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

  def now(), do: :os.system_time(:milli_seconds)

  def run(n) do
    start = now()
    points = get_points(n)

    Logger.debug("point fetched!")
    pnum = Enum.count(points)

    gp = group_points(points, %{})
    Logger.debug("group point finish!")

    p1 = around_point(gp, pnum)

    p2 =
      gp
      |> Map.values()
      |> Enum.map(fn x ->
        div(x, 2) * div(x, 2) * (pnum - x) + div(div(x, 2) * (div(x, 2) - 1), 2) * (pnum - x) +
          div(x * (x - 1) * (x - 2), 6)
      end)
      |> Enum.sum()

    Logger.info("#{p1}, #{p2}")

    res = div(pnum * (pnum - 1) * (pnum - 2), 6) - div(p1, 2) - p2
    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end

  defp around_point(gp, pnum) do
    Map.to_list(gp)
    |> Enum.map(fn {_, c} ->
      n = div(pnum - c, 2)
      c * n * (n - 1)
    end)
    |> Enum.sum()
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
