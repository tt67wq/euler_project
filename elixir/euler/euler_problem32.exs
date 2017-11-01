defmodule PandigitalProducts do
  @moduledoc """
  We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.
  The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.
  Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
  HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
  """
  require Logger

  @spec isPandigitalString(String) :: boolean
  def isPandigitalString(string) do
    cond do
      String.length(string) >= 10 -> false
      true -> in?(string, String.length(string), 1)
    end
  end

  defp in?(_string, digits, index) when index > digits, do: true
  defp in?(string, digits, index) do
    cond do
      not String.contains?(string, Integer.to_string(index)) -> false
      true -> in?(string, digits, index+1)
    end
  end

  @spec gives9PandigitalProduct(integer, integer) :: boolean
  def gives9PandigitalProduct(a, b), do: gives9PandigitalProduct(a, b, a * b)
  defp gives9PandigitalProduct(a, b, c) do
    s = Integer.to_string(a) <> Integer.to_string(b) <> Integer.to_string(c)
    cond do
      String.length(s) != 9 -> false
      true -> isPandigitalString(s)
    end
  end


  def find_all(), do: find(0, 1, [])
  defp find(a, _b, acc) when a > 100000, do: acc
  defp find(a, b, acc) when b > 100000, do: find(a + 1, a + 2, acc)
  defp find(a, b, acc) do
    cond do
      gives9PandigitalProduct(a, b) ->
	Logger.info("#{a} * #{b} = #{a * b}")
	find(a, b+1, [a * b | acc])
      String.length(Integer.to_string(a) <> Integer.to_string(b) <> Integer.to_string(a * b)) > 9 -> find(a+1, a+2, acc)
      true -> find(a, b + 1, acc)
    end
  end
end
