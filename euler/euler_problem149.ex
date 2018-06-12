defmodule Euler149 do
  @moduledoc """
  https://projecteuler.net/problem=149
  horizontal, vertical, diagonal or anti-diagonal
  """
  require Logger

  @k 2000

  def lagged_fibonacci_generator(k) when k <= 55 do
    rem(100_003 - 200_003 * k + 300_007 * k * k * k, 1_000_000) - 500_000
  end

  def lagged_fibonacci_generator(k) when k <= 4_000_000 do
    r1 = cache_lfg(k - 24)
    r2 = cache_lfg(k - 55)
    rem(r1 + r2 + 1_000_000, 1_000_000) - 500_000
  end

  def cache_lfg(k) do
    case :ets.lookup(:lagged_fibonacci, k) do
      [] ->
        v = lagged_fibonacci_generator(k)
        :ets.insert(:lagged_fibonacci, {k, v})
        v

      [{^k, value}] ->
        value
    end
  end

  def max_horizontal(mp), do: mh(mp, 0, 0)

  defp mh(_mp, index, acc) when index >= @k, do: acc

  defp mh(mp, index, acc) do
    s =
      1..2000
      |> Enum.map(fn x -> Map.fetch!(mp, index * @k + x) end)
      |> Enum.sum()

    if s > acc do
      mh(mp, index + 1, s)
    else
      mh(mp, index + 1, acc)
    end
  end

  def max_vertical(mp), do: mv(mp, 0, 0)

  defp mv(_mp, index, acc) when index >= @k, do: acc

  defp mv(mp, index, acc) do
    s =
      1..2000
      |> Enum.map(fn x -> Map.fetch!(mp, (x - 1) * @k + index + 1) end)
      |> Enum.sum()

    if s > acc do
      mv(mp, index + 1, s)
    else
      mv(mp, index + 1, acc)
    end
  end

  def max_diagonal(mp), do: md(mp, -@k, 0)

  defp md(_mp, index, acc) when index > @k, do: acc

  defp md(mp, index, acc) do
    s =
      1..2000
      |> Enum.map(fn x -> (x - 1) * @k + x - index end)
      |> Enum.map(fn x -> Map.fetch(mp, x) end)
      |> Enum.filter(fn x -> x != :error end)
      |> Enum.map(fn {_, v} -> v end)
      |> Enum.sum()

    if s > acc do
      md(mp, index + 1, s)
    else
      md(mp, index + 1, acc)
    end
  end

  def max_anti_diagonal(mp), do: mad(mp, -@k, 0)

  defp mad(_mp, index, acc) when index > @k, do: acc

  defp mad(mp, index, acc) do
    s =
      1..2000
      |> Enum.map(fn x -> x * @k - (x - 1) - index end)
      |> Enum.map(fn x -> Map.fetch(mp, x) end)
      |> Enum.filter(fn x -> x != :error end)
      |> Enum.map(fn {_, v} -> v end)
      |> Enum.sum()

    if s > acc do
      mad(mp, index + 1, s)
    else
      mad(mp, index + 1, acc)
    end
  end

  def solution() do
    # 41078532, 36742681, 44540336, 34192309
    :ets.new(:lagged_fibonacci, [:named_table])
    mp = 1..(@k * @k) |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, x, cache_lfg(x)) end)
    s1 = max_horizontal(mp)
    s2 = max_vertical(mp)
    s3 = max_diagonal(mp)
    s4 = max_anti_diagonal(mp)
    Logger.info("#{s1}, #{s2}, #{s3}, #{s4}")
  end
end
