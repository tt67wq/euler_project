defmodule EulerProblem155 do
  @moduledoc """
  https://projecteuler.net/problem=155

  https://oeis.org/A153588
  1, 3, 7, 15, 35, 77, 179, 429, 1039, 2525, 6235, 15463, 38513, 96231, 241519, 607339, 1529533, 3857447, 9743247, 24634043
  """

  require Integer
  require Logger

  @limit 18

  defp simplify({m, n}) do
    g = Integer.gcd(m, n)
    {div(m, g), div(n, g)}
  end

  defp merge(_, [], acc), do: acc

  defp merge(list, [{m, n} | t], acc) do
    bcc =
      list
      |> Enum.reduce([], fn {m1, n1}, cc ->
        [simplify({m * n1 + n * m1, n * n1}), simplify({m * m1, m1 * n + m * n1}) | cc]
      end)

    merge(list, t, acc ++ bcc)
  end

  def iter(map, n, acc) do
    list =
      1..div(n, 2)
      |> Enum.map(fn x -> {Map.fetch!(map, x), Map.fetch!(map, n - x)} end)
      |> Enum.reduce([], fn {list1, list2}, cc ->
        merge(list1, list2, []) ++ cc
      end)
      |> Enum.uniq()
      |> Enum.filter(fn x -> not MapSet.member?(acc, x) end)

    Map.put(map, n, list)
  end

  def solution() do
    init_map = %{1 => [{1, 1}], 2 => [{1, 2}, {2, 1}]}

    sl(init_map, 3, MapSet.new([{1, 1}, {1, 2}, {2, 1}]))
    |> MapSet.size()
  end

  defp sl(_map, index, acc) when index > @limit, do: acc

  defp sl(map, index, acc) do
    Logger.info("#{index}, #{MapSet.size(acc)}")
    nmap = iter(map, index, acc)
    list = Map.fetch!(nmap, index)
    sl(nmap, index + 1, MapSet.new(list) |> MapSet.union(acc))
  end
end
