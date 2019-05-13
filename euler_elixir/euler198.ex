defmodule Euler198 do
  @moduledoc false
  require Logger

  @limit 100_000_000
  @top 100

  defp sqrt(n), do: round(Float.floor(:math.sqrt(n)))

  defp p198(_, [], acc), do: acc
  defp p198(a, [h | t], acc) when h * a > div(@limit, 2), do: p198(h, t, acc)
  defp p198(a, [h | _] = stack, acc), do: p198(a, [a + h | stack], acc + 1)

  defp p1982(_, [], acc), do: acc
  defp p1982(m, [hm | t], acc) when hm * m * 2 > @limit, do: p1982(hm, t, acc)
  defp p1982(m, [hm | _] = list, acc), do: p1982(m, [hm + m | list], acc + 1)

  def run do
    q = sqrt(div(@limit, 2))
    p198(q, Enum.reverse(@top..(q - 1)), 0) + div(@limit, 2) - div(@top, 2)
  end

  def run2 do
    p1982(1, [100], 0) + div(@top, 2) - 1
  end
end
