defmodule RomanNumerals do
  @moduledoc """
  https://projecteuler.net/problem=89
  https://projecteuler.net/about=roman_numerals

  I = 1
  V = 5
  X = 10
  L = 50
  C = 100
  D = 500
  M = 1000
  """

  def solution() do
    {:ok, content} = File.read("p089_roman.txt")
    a = content |> String.split("\n")
    |> Enum.filter(fn x -> x != "" end)
    |> Enum.reduce(0, fn x, acc -> acc + String.length(x) end)

    b = content |> String.split("\n")
    |> Enum.filter(fn x -> x != "" end)
    |> Enum.map(fn x -> replace9(x) end)
    |> Enum.map(fn x -> replace90(x) end)
    |> Enum.map(fn x -> replace900(x) end)
    |> Enum.map(fn x -> replace4(x) end)
    |> Enum.map(fn x -> replace40(x) end)
    |> Enum.map(fn x -> replace400(x) end)
    # |> Enum.filter(fn x -> x |> four_consecutive? end)
    |> Enum.reduce(0, fn x, acc -> acc + String.length(x) end)
    a - b
  end

  @doc """
  是否包含四个连续
  """
  def four_consecutive?(word), do: fc(word |> to_charlist, 'a', 0)
  defp fc(_, _, count) when count == 4, do: true
  defp fc([], _, _), do: false
  defp fc([h|t], _head, _count) when h == 77, do: fc(t, h, 1)
  defp fc([h|t], head, count) when h == head, do: fc(t, h, count+1)
  defp fc([h|t], _head, _count), do: fc(t, h, 1)

  def replace9(word), do: String.replace(word, "VIIII", "IX")
  def replace90(word), do: String.replace(word, "LXXXX", "XC")
  def replace900(word), do: String.replace(word, "DCCCC", "CM")

  def replace4(word) do
    cond do
      String.contains?(word, "V") -> word
      :else -> String.replace(word, "IIII", "IV")
    end
  end

  def replace40(word) do
    cond do
      String.contains?(word, "L") -> word
      :else -> String.replace(word, "XXXX", "XL")
    end
  end

  def replace400(word) do
    cond do
      String.contains?(word, "D") -> word
      :else -> String.replace(word, "CCCC", "CD")
    end
  end
end
