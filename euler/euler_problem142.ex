defmodule PerfectSquareCollection do
  @moduledoc """
  https://projecteuler.net/problem=142
  """
  @limit 1000
  require Integer

  def sqrt?(n) do
    r = :math.sqrt(n) |> round()
    r * r == n
  end

  @doc """
  ## Example

      iex> Generator.choose([1,2,3], 2)
      [[1, 2], [1, 3], [2, 3]]
  """
  @spec choose(List, Integer) :: List
  def choose(lst, n),
    do:
      chs(lst, n)
      |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end)
      |> MapSet.to_list()

  defp chs(lst, n) when length(lst) == n, do: [lst]
  defp chs(lst, 1), do: lst |> Enum.map(fn x -> [x] end)
  defp chs([h | t], n), do: (choose(t, n - 1) |> Enum.map(fn x -> [h | x] end)) ++ choose(t, n)

  defp iter(a, _, acc) when a > @limit, do: acc
  defp iter(a, b, acc) when a == b, do: iter(a + 1, 1, acc)

  defp iter(a, b, acc) do
    cond do
      Integer.is_odd(a + b) ->
        iter(a, b + 1, acc)

      :else ->
        x = a * a + b * b
        iter(a, b + 1, Map.update(acc, x, [{a, b}], fn x -> [{a, b} | x] end))
    end
  end

  defp check([{a, b}, {c, d}]) do
    t1 = div(a * a - b * b, 2)
    t2 = div(c * c - d * d, 2)
    sqrt?(t1 + t2) and sqrt?(t1 - t2)
  end

  def solution() do
    [[{a, b}, {c, d}] | _] =
      iter(2, 1, %{})
      |> Map.values()
      |> Enum.filter(fn x -> length(x) > 1 end)
      |> Enum.reduce([], fn x, acc -> choose(x, 2) ++ acc end)
      |> Enum.filter(fn x -> check(x) end)

    x = div(a * a + b * b, 2)
    y = div(a * a - b * b, 2)
    z = div(c * c - d * d, 2)
    {x, y, z}
  end
end
