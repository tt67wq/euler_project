defmodule NonbouncyNumbers do
  @moduledoc """
  https://projecteuler.net/problem=113
  """
  @limit 100
  require Logger
  @init %{
    1 => [{:increasing, 8}, {:decreasing, 1}],
    2 => [{:increasing, 7}, {:decreasing, 2}],
    3 => [{:increasing, 6}, {:decreasing, 3}],
    4 => [{:increasing, 5}, {:decreasing, 4}],
    5 => [{:increasing, 4}, {:decreasing, 5}],
    6 => [{:increasing, 3}, {:decreasing, 6}],
    7 => [{:increasing, 2}, {:decreasing, 7}],
    8 => [{:increasing, 1}, {:decreasing, 8}],
    9 => [{:increasing, 0}, {:decreasing, 9}],
  }

  def int2list(num), do: i2l(num, [])
  defp i2l(0, acc), do: acc
  defp i2l(num, acc), do: i2l(num |> div(10), [num |> rem(10)|acc])

  def bouncy?(num), do: num |> int2list |> bouncy?(nil)
  defp bouncy?([_], :increasing), do: {false, :increasing}
  defp bouncy?([_], :decreasing), do: {false, :decreasing}
  defp bouncy?([_], nil), do: {false, :equal}
  defp bouncy?([h1, h2|t], nil) do
    cond do
      h1 > h2 -> bouncy?([h2|t], :increasing)
      h1 < h2 -> bouncy?([h2|t], :decreasing)
      :else -> bouncy?([h2|t], :nil)
    end
  end
  defp bouncy?([h1, h2|t], :decreasing) when h1 == h2, do: bouncy?([h2|t], :decreasing)
  defp bouncy?([h1, h2|t], :decreasing) when h1 < h2, do: bouncy?([h2|t], :decreasing)
  defp bouncy?([h1, h2|t], :increasing) when h1 == h2, do: bouncy?([h2|t], :increasing)
  defp bouncy?([h1, h2|t], :increasing) when h1 > h2, do: bouncy?([h2|t], :increasing)
  defp bouncy?(_, :increasing), do: {true, nil}
  defp bouncy?(_, :decreasing), do: {true, nil}

  def add(a, b), do: a + b

  def iter(mp) do
    %{
      1 => [{:increasing, 1..9 |> Enum.reduce(0, fn x, acc -> acc + Map.fetch!(mp, x)[:increasing] end) |> add(8)}, {:decreasing, 1 + Map.fetch!(mp, 1)[:decreasing]}],
      2 => [{:increasing, 2..9 |> Enum.reduce(0, fn x, acc -> acc + Map.fetch!(mp, x)[:increasing] end) |> add(7)}, {:decreasing, 1..2 |> Enum.reduce(1, fn x, acc -> Map.fetch!(mp, x)[:decreasing] + acc end) |> add(1)}],
      3 => [{:increasing, 3..9 |> Enum.reduce(0, fn x, acc -> acc + Map.fetch!(mp, x)[:increasing] end) |> add(6)}, {:decreasing, 1..3 |> Enum.reduce(1, fn x, acc -> Map.fetch!(mp, x)[:decreasing] + acc end) |> add(2)}],
      4 => [{:increasing, 4..9 |> Enum.reduce(0, fn x, acc -> acc + Map.fetch!(mp, x)[:increasing] end) |> add(5)}, {:decreasing, 1..4 |> Enum.reduce(1, fn x, acc -> Map.fetch!(mp, x)[:decreasing] + acc end) |> add(3)}],
      5 => [{:increasing, 5..9 |> Enum.reduce(0, fn x, acc -> acc + Map.fetch!(mp, x)[:increasing] end) |> add(4)}, {:decreasing, 1..5 |> Enum.reduce(1, fn x, acc -> Map.fetch!(mp, x)[:decreasing] + acc end) |> add(4)}],
      6 => [{:increasing, 6..9 |> Enum.reduce(0, fn x, acc -> acc + Map.fetch!(mp, x)[:increasing] end) |> add(3)}, {:decreasing, 1..6 |> Enum.reduce(1, fn x, acc -> Map.fetch!(mp, x)[:decreasing] + acc end) |> add(5)}],
      7 => [{:increasing, 7..9 |> Enum.reduce(0, fn x, acc -> acc + Map.fetch!(mp, x)[:increasing] end) |> add(2)}, {:decreasing, 1..7 |> Enum.reduce(1, fn x, acc -> Map.fetch!(mp, x)[:decreasing] + acc end) |> add(6)}],
      8 => [{:increasing, 8..9 |> Enum.reduce(0, fn x, acc -> acc + Map.fetch!(mp, x)[:increasing] end) |> add(1)}, {:decreasing, 1..8 |> Enum.reduce(1, fn x, acc -> Map.fetch!(mp, x)[:decreasing] + acc end) |> add(7)}],
      9 => [{:increasing, 0}, {:decreasing, 1..9 |> Enum.reduce(1, fn x, acc -> Map.fetch!(mp, x)[:decreasing] + acc end) |> add(8)}]
    }
  end

  def solution() do
    sl(2, @init, [])
    |> Enum.map(fn x -> 1..9 |> Enum.map(fn y ->
      r = Map.fetch!(x, y)
      r[:increasing] + r[:decreasing]
    end)
    |> Enum.sum() end)
    |> Enum.sum()
    |> add(@limit * 9)
  end

  defp sl(index, _, acc) when index > @limit, do: acc
  defp sl(index, mp, acc), do: sl(index+1, iter(mp), [mp|acc])

  
end
