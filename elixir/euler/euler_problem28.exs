defmodule Euler do
  @moduledoc """
  Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

      21 22 23 24 25
      20  7  8  9 10
      19  6  1  2 11
      18  5  4  3 12
      17 16 15 14 13

  It can be verified that the sum of the numbers on the diagonals is 101.

  What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
  """  
  require Logger
  def sum_of_diagonals(level), do: sum(level, 1, 0)

  def out_sum(1), do: 1
  def out_sum(l), do: 2 * ((2 * l - 1) * (2 * l - 1) + (2 * (l - 1) - 1) * (2 * (l - 1) - 1) + 2 * (l - 1))

  defp sum(level, index, acc) when index > level, do: acc
  defp sum(level, index, acc) do
    sum(level, index+1, acc + out_sum(index))
  end

end
