defmodule Euler204 do
  @moduledoc false

  @top 1_000_000_000

  use Bitwise
  require Logger

  #### prime sieve
  def sieve(max, i, acc) when i * i > max, do: acc

  def sieve(max, i, acc) do
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

  #### prime sieve finished

  defp iter(_, [], acc), do: acc

  defp iter(ps, bcc, acc) do
    nbcc =
      bcc
      |> Enum.map(fn {v, m} ->
        ps
        |> Enum.filter(fn x -> x >= m end)
        |> Enum.filter(fn x -> x * v <= @top end)
        |> Enum.map(fn x -> {x * v, x} end)
      end)
      |> List.flatten()

    iter(ps, nbcc, acc + Enum.count(nbcc))
  end

  def run do
    ps = prime_sieve(100)
    iter(ps, Enum.map(ps, fn x -> {x, x} end), Enum.count(ps)) + 1
  end
end
