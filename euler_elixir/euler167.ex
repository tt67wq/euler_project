defmodule Euler167 do
  @moduledoc """
  https://projecteuler.net/problem=167
  """
  require Logger

  @top 20

  def ulam(a, b), do: ulam_iter(MapSet.new([a + b]), MapSet.new(), 0, [b, a])

  defp ulam_iter(_, _, @top, acc), do: Enum.reverse(acc)

  defp ulam_iter(set, jump_set, index, acc) do
    next = Enum.min(set)

    set = MapSet.delete(set, next)

    # 重复的加入jump_set
    new_jump_set =
      Enum.map(acc, fn x -> x + next end)
      |> Enum.filter(fn x -> MapSet.member?(set, x) end)
      |> Enum.reduce(jump_set, fn x, acc -> MapSet.put(acc, x) end)

    new_set =
      Enum.map(acc, fn x -> x + next end)
      |> Enum.reduce(set, fn x, acc -> MapSet.put(acc, x) end)

    ulam_iter(MapSet.difference(new_set, new_jump_set), new_jump_set, index + 1, [next | acc])
  end
end
