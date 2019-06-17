defmodule Euler210 do
  @moduledoc false

  @r 8

  # 1598174770174689500
  require Logger

  def all do
    for a <- -@r..@r,
        b <- -@r..@r,
        abs(a) + abs(b) <= @r do
      {a, b}
    end
  end

  def test do
    all()
    |> Enum.filter(fn {x, y} -> check(x, y) end)
  end

  defp check(x, y) when x == y, do: false
  defp check(x, y) when x + y == 0, do: false
  defp check(x, y) when x + y < 0, do: true
  defp check(x, y) when x + y > div(@r, 2), do: true

  defp check(x, y) do
    d = x * x + y * y

    if d / (x + y) < div(@r, 4) do
      true
    else
      false
    end
  end

  ######### real shit #########

  def none_circle_part(r) do
    s = 1..r |> Enum.sum()
    h = div(4 * s - r, 2) - div(r, 2)
    h + div(h, 2)
  end

  def circle_part(4), do: 0

  def circle_part(r) do
    e = Float.floor(r * (1 / :math.sqrt(2) - 1 / 2) / 4) |> round()

    shan =
      if e == 0 do
        0
      else
        r8 = div(r, 8)
        r32 = div(r * r, 32)

        p =
          1..e
          |> Enum.map(fn x -> count_y(x, r8, r32) end)
          |> Enum.sum()

        p * 4
      end

    r4 = div(r, 4) + 1
    r4 * r4 - r4 - 2 + shan
  end

  defp count_y(x, r8, r32) do
    t = x + r8
    m = r32 - t * t
    sq = :math.sqrt(m)
    n = round(Float.ceil(r8 - sq))
    (r8 - n) * 2 + 1
  end

  def run(r) do
    none_circle_part(r) + circle_part(r)
  end
end
