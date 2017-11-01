defmodule DoubleBasePalindromes do
  @moduledoc """
  The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.
  Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
  (Please note that the palindromic number, in either base, may not include leading zeros.)
  """
  require Logger
  require Integer

  def palindromic?(number), do: String.reverse(Integer.to_string(number)) == Integer.to_string(number)
  def palindromic_list?(number), do: Enum.reverse(number) == number

  def decimal2binary(number), do: d2b(number, number, [])
  defp d2b(_number, 0, acc), do: acc
  defp d2b(number, x, acc), do: d2b(number, div(x, 2), [rem(x, 2)|acc])

  def findall(), do: findall(1000000, 0, [])
  def findall(m, m, acc), do: acc
  def findall(m, x, acc) do
    cond do
      Integer.is_even(x) -> findall(m, x+1, acc)
      palindromic?(x) ->
	cond do
	  palindromic_list?(decimal2binary(x)) ->
	    Logger.info(x)
	    findall(m, x+1, [x|acc])
	  true -> findall(m, x+1, acc)
	end
      true->
	findall(m, x+1, acc)
    end
  end
end
