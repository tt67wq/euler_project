defmodule PowerDigitSum do
  @moduledoc """
  215 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
  What is the sum of the digits of the number 21000?
  """

  @spec digit_sum(integer) :: integer
  def digit_sum(n), do: digit_sum(n, n, 0)
  defp digit_sum(_n, 0, acc), do: acc
  defp digit_sum(n, index, acc), do: digit_sum(n, div(index, 10), acc + rem(index, 10))
end
