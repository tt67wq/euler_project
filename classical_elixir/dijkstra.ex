defmodule Dijkstra do
  @moduledoc """
  http://wiki.jikexueyuan.com/project/easy-learn-algorithm/dijkstra.html
  """

  @total 6

  def dij_iter(_, _, acc, @total), do: acc

  def dij_iter(mp, bcc, acc, index) do
    # fix one
    {k, v} =
      Map.to_list(bcc)
      |> Enum.min_by(fn {x, _} -> x end)

    # do slack
    nbcc =
      Map.get(mp, k)
      |> Map.to_list()
      |> Enum.reduce(Map.delete(bcc, k), fn {x, y}, tcc ->
        Map.update(tcc, x, v + y, fn z -> min(z, v + y) end)
      end)

    dij_iter(mp, nbcc, Map.put(acc, k, v), index + 1)
  end

  def run() do
    mp = %{
      1 => %{2 => 1, 3 => 12},
      2 => %{3 => 9, 4 => 3},
      3 => %{5 => 5},
      4 => %{3 => 4, 5 => 13, 6 => 15},
      5 => %{6 => 4},
      6 => %{}
    }

    dij_iter(mp, Map.get(mp, 1), %{}, 0)
  end
end
