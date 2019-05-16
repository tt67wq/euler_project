defmodule PrimeSieve do
  @moduledoc """
  筛子
  """
  use Bitwise

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
  defp remove(i, j, max, acc), do: remove(i, j + 2 * i, max, remove_from_sieve(acc, j))

  @spec in_sieve?(term(), integer) :: boolean()
  def in_sieve?(sieve, i) do
    a =
      i
      |> div(16)
      |> :array.get(sieve)

    b =
      i
      |> rem(16)
      |> div(2)
      |> bsl(2)

    (a &&& b) == 0
  end

  @spec remove_from_sieve(term(), integer) :: term()
  def remove_from_sieve(sieve, i) do
    index = div(i, 16)

    a =
      index
      |> :array.get(sieve)

    b =
      i
      |> rem(16)
      |> div(2)
      |> bsl(2)

    :array.set(index, bor(a, b), sieve)
  end

  def run(max) do
    ps = sieve(max, 3, :array.new({:default, 1}))

    3..max
    |> Enum.filter(fn x -> rem(x, 2) == 1 end)
    |> Enum.filter(fn x -> in_sieve?(ps, x) end)
  end
end
