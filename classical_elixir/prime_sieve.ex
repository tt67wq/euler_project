defmodule PrimeSieve do
  @moduledoc """
  筛子
  """
  use Bitwise
  require Logger

  def sqrt(n), do: n |> :math.sqrt() |> Float.floor() |> round

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

  def now(), do: :os.system_time(:milli_seconds)

  def run(max) do
    ps = sieve(max, 3, :array.new(max, {:default, 1}))

    3..max
    |> Enum.filter(fn x -> rem(x, 2) == 1 end)
    |> Enum.filter(fn x -> in_sieve?(ps, x) end)
  end
end
