defmodule Euler170 do
  @moduledoc """
  https://projecteuler.net/problem=170
  """
  require Integer
  require Logger

  def num2digits(num), do: digits(num, [])
  defp digits(0, acc), do: Enum.sort(acc)
  defp digits(num, acc), do: digits(div(num, 10), [rem(num, 10) | acc])

  def digits2num(list), do: d2n(list, 0)
  defp d2n([], acc), do: acc
  defp d2n([h | t], acc), do: d2n(t, acc * 10 + h)

  def permutations(list) do
    list
    |> Enum.sort()
    |> Enum.reverse()
    |> Stream.unfold(fn
      [] -> nil
      p -> {p, next_permutation(p)}
    end)
  end

  defp next_permutation(permutation) do
    if permutation == permutation |> Enum.sort() do
      []
    else
      permutation
      |> split
      |> heal
    end
  end

  defp split(permutation) do
    permutation
    |> Enum.reverse()
    |> Enum.reduce({20, false, [], []}, fn x, {prev, split, first, last} ->
      case split do
        false -> {x, x > prev, first, [x | last]}
        true -> {x, true, [x | first], last}
      end
    end)
    |> (fn {_, _, first, last} -> {first, last} end).()
  end

  defp heal({first, [h | _] = last}) do
    next = last |> Enum.filter(&(&1 < h)) |> Enum.max()
    rest = (last -- [next]) |> Enum.sort() |> Enum.reverse()
    first ++ [next] ++ rest
  end

  def test() do
    permutations([9, 8, 7, 6, 5, 4, 3, 2, 1, 0])
    |> Stream.map(fn x -> Enum.map(1..9, fn y -> Enum.split(x, y) end) end)
    |> Enum.filter(fn x -> x end
    )
  end

  def check(a, b) do
    2..9
    |> Enum.filter(fn x -> rem(a, x) == 0 and rem(b, x) == 0 end)
    |> Enum.map(fn x -> {x, num2digits(div(a, x)), num2digits(div(b, x))} end)
    |> Enum.filter(fn {x, y, z} -> Enum.sort([x | y ++ z]) == [0, 1, 2, 3, 4, 5, 6, 7, 8, 9] end)
  end
end
