defmodule Euler154 do
  @moduledoc """
  https://projecteuler.net/problem=154

  参考资料 帕斯卡四面体
  https://en.wikipedia.org/wiki/Pascal%27s_pyramid
  """
  @level 200_000
  require Logger

  def start() do
    :ets.new(:eu154_2, [:named_table])
    :ets.new(:eu154_5, [:named_table])
  end

  def containP(n, p), do: cp(n, p, 0)

  defp cp(0, _p, acc), do: acc

  defp cp(n, p, acc) do
    case rem(n, p) do
      0 -> cp(div(n, p), p, acc + 1)
      _ -> acc
    end
  end

  def cacheFacContains2(n, mp) do
    case :ets.lookup(:eu154_2, n) do
      [{^n, value}] ->
        value

      [] ->
        v = factorialContains2(n, mp)
        :ets.insert(:eu154_2, {n, v})
        v
    end
  end

  def cacheFacContains5(n, mp) do
    case :ets.lookup(:eu154_5, n) do
      [{^n, value}] ->
        value

      [] ->
        v = factorialContains5(n, mp)
        :ets.insert(:eu154_5, {n, v})
        v
    end
  end

  def factorialContains2(n, mp), do: fcp2(n, mp, 0)
  defp fcp2(0, _mp2, acc), do: acc

  defp fcp2(n, mp2, acc) do
    case Map.fetch(mp2, n) do
      :error -> fcp2(n - 1, mp2, acc)
      {:ok, v} -> fcp2(n - 1, mp2, acc + v)
    end
  end

  def factorialContains5(n, mp), do: fcp5(n, mp, 0)
  defp fcp5(0, _mp5, acc), do: acc

  defp fcp5(n, mp5, acc) do
    case Map.fetch(mp5, n) do
      :error -> fcp5(n - 1, mp5, acc)
      {:ok, v} -> fcp5(n - 1, mp5, acc + v)
    end
  end

  def counter2and5(level, index, base2, base5, mp2, mp5) do
    {
      base2 -
        (cacheFacContains2(level - index, mp2) + cacheFacContains2(@level - level, mp2) +
           cacheFacContains2(index, mp2)),
      base5 -
        (cacheFacContains5(level - index, mp5) + cacheFacContains5(@level - level, mp5) +
           cacheFacContains5(index, mp5))
    }
  end

  defp sl(level, _index, _base2, _base5, _mp2, _mp5, acc) when level > @level, do: acc

  defp sl(level, index, base2, base5, mp2, mp5, acc) when index > level do
    Logger.info("#{level}, #{index}")
    sl(level + 1, 0, base2, base5, mp2, mp5, acc)
  end

  defp sl(level, index, base2, base5, mp2, mp5, acc) do
    {c2, c5} = counter2and5(0, 0, base2, base5, mp2, mp5)

    cond do
      c2 >= 12 and c5 >= 12 -> sl(level, index + 1, base2, base5, mp2, mp5, acc + 1)
      :else -> sl(level, index + 1, base2, base5, mp2, mp5, acc)
    end
  end

  def solution() do
    start()
    mp2 = 0..@level |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, x, containP(x, 2)) end)
    mp5 = 0..@level |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, x, containP(x, 5)) end)
    base2 = cacheFacContains2(@level, mp2)
    base5 = cacheFacContains5(@level, mp5)
    sl(0, 0, base2, base5, mp2, mp5, 0)
  end
end
