defmodule Euler do
  @moduledoc """
  Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

  1634 = 14 + 64 + 34 + 44
  8208 = 84 + 24 + 04 + 84
  9474 = 94 + 44 + 74 + 44
  As 1 = 14 is not a sum it is not included.

  The sum of these numbers is 1634 + 8208 + 9474 = 19316.

  Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
  """

  def perfect?(n), do: perfect?(n, n, 0)
  # def perfect? do
  #   receive do
  #     {:ok, x} -> perfect?(x, x, 0)
  #   end
  #   perfect?
  # end
  defp perfect?(n, 0, acc), do: acc == n
  defp perfect?(n, x, acc), do: perfect?(n, div(x, 10), acc + :math.pow(rem(x, 10), 5))

  def util(n), do: util(n, 2, [])
  defp util(n, n, acc), do: acc
  defp util(n, index, acc) do
    cond do
      perfect?(index) -> util(n, index+1, [index | acc])
      true -> util(n, index+1, acc)
    end
  end
end
