defmodule Euler210 do
  @moduledoc false

  @r 4

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
end
