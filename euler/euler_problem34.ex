defmodule DigitFactorials do
  @moduledoc """
  145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
  Find the sum of all numbers which are equal to the sum of the factorial of their digits.
  Note: as 1! = 1 and 2! = 2 are not sums they are not included.
  """
  @doc """
  阶乘
  """
  def factorial(n), do: fac(n, 1, 1)
  defp fac(n, index, acc) when index > n, do: acc
  defp fac(n, index, acc), do: fac(n, index + 1, acc * index)

  def curious?(num), do: cur(num, 0) == num
  defp cur(0, acc), do: acc
  defp cur(num, acc), do: cur(div(num, 10), acc + (rem(num, 10) |> factorial))

  def run() do
    3..9_999_999
    |> Enum.filter(fn x -> curious?(x) end)
    |> Enum.sum()
  end
end
