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
  @limit 10000

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

  def abchit_group(num, one_facs) do
    for x <- [1 | one_facs], x < num, gcd(x, num - x) == 1 do
      [x, num - x, num]
    end
    |> Enum.map(fn x -> x |> Enum.sort() end)
    |> Enum.map(fn [a, b, c] -> {a, b, c} end)
    |> Enum.uniq()
    |> Enum.filter(fn {a, b, c} -> rad(a) * rad(b) * rad(c) < num end)
  end

  # def get_all_candidates(), do: get_all(2, []) |> Enum.sort()

  # defp get_all(num, acc) do
  #   facs = factorization(num)

  #   cond do
  #     Enum.member?(acc, num) ->
  #       get_all(num + 1, acc)

  #     length(facs) == 1 ->
  #       bcc = func(1, num, [])

  #       cond do
  #         length(bcc) > 0 -> get_all(num + 1, bcc ++ acc)
  #         :else -> acc
  #       end

  #     :else ->
  #       get_all(num + 1, acc)
  #   end
  # end

  # defp func(p, num, acc) do
  #   a = round(:math.pow(num, p))

  #   cond do
  #     a > @limit -> acc
  #     :else -> func(p + 1, num, [a | acc])
  #   end
  # end

  # def solution() do
  #   one_facs = get_all_candidates()

  #   data =
  #     5..@limit
  #     |> Enum.map(fn x -> abchit_group(x, one_facs) end)
  #     |> Enum.filter(fn x -> length(x) != 0 end)

  #   Logger.info(fn -> inspect(data, pretty: true, limit: 30000) end)

  #   data
  #   |> Enum.map(fn x -> Enum.map(x, fn {_, _, y} -> y end) end)
  #   |> Enum.map(fn x -> Enum.sum(x) end)
  #   |> Enum.sum()
  # end
end
