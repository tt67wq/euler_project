defmodule Euler203 do
  @moduledoc false
  use Bitwise
  require Logger

  def pascal(), do: pascal_gene(%{0 => [1], 1 => [1, 1]}, 1)

  defp pascal_gene(state, 51), do: state

  defp pascal_gene(state, level) do
    nums = Map.get(state, level)

    Map.put(state, level + 1, level_iter(nums, []))
    |> pascal_gene(level + 1)
  end

  defp level_iter([h1, h2], acc), do: [1 | Enum.reverse([1, h1 + h2 | acc])]
  defp level_iter([h1, h2 | t], acc), do: level_iter([h2 | t], [h1 + h2 | acc])

  ##### prime sieve
  defp sieve(max, i, acc) when i * i > max, do: acc

  defp sieve(max, i, acc) do
    case in_sieve?(acc, i) do
      true ->
        sieve(max, i + 2, remove(i, i * i, max, acc))

      _ ->
        sieve(max, i + 2, acc)
    end
  end

  defp remove(_, j, max, acc) when j > max, do: acc

  defp remove(i, j, max, acc), do: remove(i, j + bsl(i, 1), max, remove_from_sieve(acc, j))

  defp pos_fix(i), do: i |> bsr(1) |> bsl(1)

  @spec in_sieve?(term(), integer) :: boolean()
  def in_sieve?(sieve, i) do
    a = :array.get(i, sieve)

    b = pos_fix(i)

    (a &&& b) == 0
  end

  @spec remove_from_sieve(term(), integer) :: term()
  def remove_from_sieve(sieve, i) do
    a = :array.get(i, sieve)
    b = pos_fix(i)

    :array.set(i, bor(a, b), sieve)
  end

  def prime_sieve(max) do
    ps = sieve(max, 3, :array.new(max, {:default, 1}))
    Logger.info("sieve finish")

    res =
      3..max
      |> Enum.filter(fn x -> rem(x, 2) == 1 end)
      |> Enum.filter(fn x -> in_sieve?(ps, x) end)

    [2 | res]
  end

  ##### prime sieve

  defp squarefree?(num, ps) do
    flag =
      ps
      |> Enum.filter(fn x -> x * x <= num end)
      |> Enum.any?(fn x -> rem(num, x * x) == 0 end)

    not flag
  end

  def run do
    ps = prime_sieve(11_243_248)
    tr = pascal()
    iter(ps, tr, 0, [])
  end

  defp iter(_, _, 51, acc), do: Enum.uniq(acc)

  defp iter(ps, tr, index, acc) do
    tmp =
      tr
      |> Map.get(index)
      |> Enum.take(div(index, 2) + 1)
      |> Enum.filter(fn x -> squarefree?(x, ps) end)

    iter(ps, tr, index + 1, acc ++ tmp)
  end
end
