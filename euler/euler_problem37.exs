defmodule TruncatablePrimes do
  @moduledoc """
  The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right,
  and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
  Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
  NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
  """
  require Logger
  def prime?(1), do: false
  def prime?(x), do: prime(x, 2, [])
  defp prime(x, y, acc) when y * y > x, do: length(acc) == 0
  defp prime(_x, _y, acc) when length(acc) > 0, do: false
  defp prime(x, y, acc) do
    cond do
      rem(x, y) == 0 -> prime(x, y+1, [y|acc])
      true -> prime(x, y+1, acc)
    end
  end

  def leftTruncatablePrime?(x), do: left(Integer.to_charlist(x), x)
  defp left([_h|t], x) do
    cond do
      length(t) == 0 -> prime?(x)
      prime?(x) -> left(t, List.to_integer(t))
      true -> false
    end
  end

  def rightTruncatablePrime?(x), do: right(Integer.to_charlist(x), x)
  defp right(y, x) do
    [_h|t] = Enum.reverse(y)
    cond do
      length(t) == 0 -> prime?(x)
      prime?(x) -> right(Enum.reverse(t), List.to_integer(Enum.reverse(t)))
      true -> false
    end
  end

  def findall(), do: findall(9, [])
  def findall(x, acc) do
    cond do
      length(acc) == 11 -> acc
      leftTruncatablePrime?(x) and rightTruncatablePrime?(x) ->
	Logger.info(x)
	findall(x+2, [x|acc])
      true -> findall(x+2, acc)
    end
  end
end
