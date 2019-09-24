defmodule Euler143 do
  @moduledoc """
  https://projecteuler.net/problem=143

  p * p + r * r + p * r = c * c
  的通项公式为
  p = 2uv + v^2
  r = u^2 - v^2
  c = u^2 + v^2 + uv
  """
  @limit 120_000
  require Integer
  require Logger

  def sqrt?(n) do
    r = :math.sqrt(n) |> round()
    r * r == n
  end

  def check(p, q), do: (p * p + q * q + p * q) |> sqrt?()

  def sequnce(), do: seq(1, 1, [])

  defp seq(u, _, acc) when u * u > @limit, do: acc
  defp seq(u, v, acc) when u == v, do: seq(u + 1, 1, acc)

  defp seq(u, v, acc) do
    cond do
      Integer.gcd(u, v) == 1 ->
        p = 2 * u * v + v * v
        r = u * u - v * v

        cond do
          p > r -> seq(u, v + 1, [{p, r} | acc])
          :else -> seq(u, v + 1, [{r, p} | acc])
        end

      :else ->
        seq(u, v + 1, acc)
    end
  end

  def group(data), do: gp(data, %{})

  defp gp([], acc), do: acc
  defp gp([{p, r} | t], acc), do: gp(t, Map.update(acc, p, [r], fn x -> [r | x] end))

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

  def extend({p, r}), do: extend({p, r}, 1, [])

  defp extend({p, r}, index, acc) do
    cond do
      (p + r) * index < @limit -> extend({p, r}, index + 1, [{p * index, r * index} | acc])
      :else -> acc
    end
  end

  def solution() do
    table =
      sequnce()
      |> Enum.reduce([], fn x, acc -> acc ++ extend(x) end)
      |> Enum.sort_by(fn {x, _} -> x end)
      |> group()

    table
    |> Map.keys()
    |> Enum.filter(fn x -> length(Map.fetch!(table, x)) > 1 end)
    |> Enum.map(fn x ->
      {x, Map.fetch!(table, x) |> choose(2) |> Enum.filter(fn [p, q] -> check(p, q) end)}
    end)
    |> Enum.filter(fn {_, list} -> length(list) > 0 end)
    |> Enum.map(fn {x, list} ->
      list |> Enum.map(fn [p, q] -> [x, p, q] |> Enum.sort() end) |> Enum.uniq()
    end)
    |> Enum.reduce([], fn x, acc -> x ++ acc end)
    |> Enum.map(fn x -> x |> Enum.sort() end)
    |> Enum.map(fn x -> Enum.sum(x) end)
    |> Enum.filter(fn x -> x <= @limit end)
    |> Enum.uniq()
    |> Enum.sum()
  end
end
