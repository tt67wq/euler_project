defmodule CodedTriangleNumbers do
  @moduledoc """
  The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:

  1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

  By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value.
  For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle number then we shall call the word a triangle word.
  Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words?
  """
  require Logger

  @letterMap "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z" |> String.split() |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, x, length(Map.keys(acc)) + 1) end)
  
  @spec triangle(Integer) :: Integer
  def triangle(n), do: div(n * (n + 1), 2)


  @spec triangle?(Integer) :: boolean
  def triangle?(x), do: triangle?(x, 1)
  defp triangle?(x, index) do
    cond do
      triangle(index) == x -> true
      triangle(index) > x -> false
      :else -> triangle?(x, index+1)
    end
  end

  @spec calculateWordValue(BitString) :: Integer
  def calculateWordValue(word) do
    Logger.info("#{word}")
    0..String.length(word)-1 |> Enum.map(fn x -> String.at(word, x) end) |> Enum.reduce(0, fn x, acc -> acc + Map.get(@letterMap, x) end)
  end

  @spec countTriangleWords(List) :: Integer
  def countTriangleWords(lst), do: lst |> Enum.filter(fn x -> calculateWordValue(x) |> triangle?() end) |> length()

end
