defmodule CuboidLayers do
  @moduledoc """
  https://projecteuler.net/problem=126
  """

  require Logger
  @limit 500000

  def cub(x, y, z, t), do: 4 * (t-1) * (x+y+z+t-2) + 2 * (x * y + y * z + x * z)

  def solution() do
    m = sl(1,1,1,1,%{})
    m |> Map.keys()
    |> Enum.map(fn x -> {x, Map.fetch!(m, x)} end)
    |> Enum.filter(fn {_, x} -> x == 1000 end)
    |> Enum.sort_by(fn {x, _} -> x end)
  end

  defp sl(1, b, c, t, m) when b > c, do: sl(1, 1, c+1, t, m)
  defp sl(a, b, c, t, m) when a > b, do: sl(1, b+1, c, t, m)
  defp sl(a, b, c, t, m) do
    r = cub(a, b, c, t)
    cond do
      r > @limit ->
	cond do
	  a == b and b == c and t == 1 -> m
	  :else -> sl(a+1, b, c, 1, m)
	end
	:else -> sl(a, b, c, t+1, Map.update(m, r, 1, fn x -> x+1 end))
    end
  end
end
