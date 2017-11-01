defmodule NumberLetterCounts do
  @moduledoc """
  https://projecteuler.net/problem=17
  """
  @num_word_map %{
    0 => "",
    1 => "one",
    2 => "two",
    3 => "three",
    4 => "four",
    5 => "five",
    6 => "six",
    7 => "seven",
    8 => "eight",
    9 => "nine",
    10 => "ten",
    11 => "eleven",
    12 => "twelve",
    13 => "thirteen",
    15 => "fifteen",
    18 => "eighteen",
    20 => "twenty",
    30 => "thirty",
    40 => "forty",
    50 => "fifty",
    80 => "eighty"
  }

  def get_from_map(num) do
    case @num_word_map |> Map.fetch(num) do
      {:ok, value} -> value
      :error -> nil
    end
  end

  
  def num2word(num) when num <= 10, do: get_from_map(num)
  def num2word(num) when num <= 20 do
    v = get_from_map(num)
    case v do
      nil -> (num |> rem(10) |> num2word()) <> "teen"
      _ -> v
    end
  end

  def num2word(num) when num < 100 do
    v = get_from_map(num)
    case v do
      nil ->
	case num |> rem(10) do
	  0 -> (num |> div(10) |> num2word()) <> "ty"
	  _ -> (((num |> div(10)) * 10) |> num2word()) <> "-" <> (num |> rem(10) |> num2word())
	end
      _ -> v
    end
  end

  def num2word(num) when num < 1000 do
    case num |> rem(100) do
      0 -> (num |> div(100) |> num2word()) <> " hundred"
      _ -> (((num |> div(100)) * 100) |> num2word()) <> " and " <> (num |> rem(100) |> num2word())
    end
  end

  def num2word(num) when num == 1000, do: "one thousand"

  def letter_count(word) do
    word |> String.replace("-", "")
    |> String.replace(" ", "")
    |> String.length()
  end


  def solution() do
    1..1000 |> Enum.map(fn x -> num2word(x) end)
    |> Enum.map(fn x -> letter_count(x) end)
    |> Enum.sum()
  end



end
