defmodule CyclicalFigurateNumbers do
  @moduledoc """
  https://projecteuler.net/problem=61
  """
  require Logger
  def ride(a, b), do: a * b

  def triangle(n), do: n |> ride(n + 1) |> div(2)
  def square(n), do: ride(n, n)
  def pentagonal(n), do: n |> ride(3 * n - 1) |> div(2)
  def hexagonal(n), do: n |> ride(2 * n - 1)
  def heptagonal(n), do: n |> ride(5 * n - 3) |> div(2)
  def octagonal(n), do: n |> ride(3 * n - 2)

  def cycli_match_last([a|_t], b), do: cycli_match(a, b)
  def cycli_match(a, b), do: rem(a, 100) == div(b, 100)

  @doc """
  ## Example
  
      iex> Generator.arrange([1, 2, 3])
      [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
  """
  @spec arrange(List) :: List
  def arrange(lst), do: arg(lst) |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end) |> MapSet.to_list()
  defp arg(lst) when length(lst) == 1, do: [lst]
  defp arg([h|t]), do: arrange(t) |> Enum.reduce([], fn x, acc -> insert(h, x) ++ acc end)
  defp insert(n, lst), do: 0..length(lst) |> Enum.map(fn x -> List.insert_at(lst, x, n) end)

  @doc """
  得到满足条件的咬尾蛇列表
  """
  def get_cycli_list(order, m) do
    lst = order |> Enum.map(fn x -> Map.fetch!(m, x) end)
    lst1 = for a <- Enum.at(lst, 0),
      b <- Enum.at(lst, 1),
      cycli_match(a, b), do: [b, a]
    [_, _ | t] = lst
    acc = gcl(t, lst1)
    acc |> Enum.filter(fn x -> cycli_match(Enum.at(x, -1), Enum.at(x, 0)) end)
    |> Enum.map(fn x -> list2set(x) end)
  end

  def list2set(lst), do: lst |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end)

  defp gcl([], acc), do: acc |> Enum.map(fn x -> x |> Enum.reverse() end)
  defp gcl([h|t], acc) do
    l = for a <- acc,
      b <- h,
      cycli_match_last(a, b), do: [b|a]
    gcl(t, l)
  end



  def solution() do
    trs = 45..140 |> Enum.map(fn x -> triangle(x) end)
    sqs = 32..99 |> Enum.map(fn x -> square(x) end)
    pes = 26..82 |> Enum.map(fn x -> pentagonal(x) end)
    hexs = 23..70 |> Enum.map(fn x -> hexagonal(x) end)
    heps = 21..63 |> Enum.map(fn x -> heptagonal(x) end)
    ocs = 19..58 |> Enum.map(fn x -> octagonal(x) end)
    lmap = %{
      1 => trs,
      2 => sqs,
      3 => pes,
      4 => hexs,
      5 => heps,
      6 => ocs
    }
    order = arrange([1,2,3,4,5,6])
    order |> Stream.map(fn x -> get_cycli_list(x, lmap) end)
    |> Stream.filter(fn x -> length(x) > 0 end)
    |> Enum.to_list()
    |> list2set()
  end
end
