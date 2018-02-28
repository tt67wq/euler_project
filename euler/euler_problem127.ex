defmodule AbcHits do
  @moduledoc """
  The radical of n, rad(n), is the product of distinct prime factors of n. For example, 504 = 23 × 32 × 7, so rad(504) = 2 × 3 × 7 = 42.

  We shall define the triplet of positive integers (a, b, c) to be an abc-hit if:

  GCD(a, b) = GCD(a, c) = GCD(b, c) = 1
  a < b
  a + b = c
  rad(abc) < c
  For example, (5, 27, 32) is an abc-hit, because:

  GCD(5, 27) = GCD(5, 32) = GCD(27, 32) = 1
  5 < 27
  5 + 27 = 32
  rad(4320) = 30 < 32
  It turns out that abc-hits are quite rare and there are only thirty-one abc-hits for c < 1000, with ∑c = 12523.

  Find ∑c for c < 120000.
  """

  require Logger
  @limit 120000

  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  @doc """
  质因数分解
  """
  @spec factorization(integer) :: map
  def factorization(n), do: fac(n, 2, [])
  defp fac(n, index, acc) when index * index > n and n > 1, do: [n | acc]

  defp fac(n, index, acc) do
    case rem(n, index) == 0 do
      true -> fac(div(n, index), index, [index | acc])
      _ -> fac(n, index + 1, acc)
    end
  end

  def rad(1), do: 1
  def rad(num), do: factorization(num) |> Enum.uniq() |> Enum.reduce(1, fn x, acc -> x * acc end)

  def all_rad(), do: 1..@limit |> Enum.map(fn x -> rad(x) end) |> Enum.uniq()
  def all_rad_map(), do: 1..@limit |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, x, rad(x)) end)

  def revert_all_rad_map() do
    1..@limit
    |> Enum.reduce(%{}, fn x, acc -> Map.update(acc, rad(x), [x], fn y -> [x | y] end) end)
  end

  def rad_less(rads, re_rad_map, num) do
    # Logger.info(inspect(rads))
    rads |> Enum.filter(fn x -> x <= num end)
    |> Enum.reduce([], fn x, acc -> Map.fetch!(re_rad_map, x) ++ acc end)
  end

  def all_a(c, rad_map, re_rad_map, rads) do
    Logger.info("testing #{c}")
    top = div(c, 2 * Map.fetch!(rad_map, c))

    rad_less(rads, re_rad_map, top)
    |> Enum.filter(fn x -> x < c end)
    |> Enum.filter(fn x -> x < c - x end)
    |> Enum.filter(fn x -> gcd(x, c) == 1 end)

  end

  def solution() do
    rad_map = all_rad_map()
    re_rad_map = revert_all_rad_map()
    rads = all_rad()

    for c <- 2..@limit,
        a <- all_a(c, rad_map, re_rad_map, rads),
        Map.fetch!(rad_map, a) * Map.fetch!(rad_map, c - a) * Map.fetch!(rad_map, c) < c do
      {a, c - a, c}
    end
    |> Enum.map(fn {_, _, x} -> x end)
    |> Enum.sum()
  end
end
