defmodule AnagramicSquares do
  @moduledoc """
  https://projecteuler.net/problem=98

  By replacing each of the letters in the word CARE with 1, 2, 9, and 6 respectively, we form a square number: 1296 = 36^2. What is remarkable is that, by using the same digital substitutions, the anagram, RACE, 
  also forms a square number: 9216 = 96^2. We shall call CARE (and RACE) a square anagram word pair and specify further that leading zeroes are not permitted, neither may a different letter have the same digital value as another letter.
  Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, find all the square anagram word pairs (a palindromic word is NOT considered to be an anagram of itself).
  What is the largest square number formed by any member of such a pair?
  NOTE: All anagrams formed must be contained in the given text file.
  """
  @limit 999999999
  require Logger
  
  def solution() do
    {_, content} = File.read("p098_words.txt")
    content |> String.split(",")
    |> Enum.map(fn x -> x |> String.replace("\"", "") end)
    |> map_by_charactor()
    |> Map.values |> Enum.filter(fn x -> length(x) == 2 end)
    |> Enum.sort_by(fn [x|_] -> String.length(x) end)
    |> Enum.reverse()
    |> Enum.map(fn [x1, x2] -> {[x1, x2], generate_square(x1, x2)} end)
  end

  def word_match?([word1, word2], [num1, num2]) do
    # Logger.info("word1: #{word1}, word2: #{word2}, num1: #{num1}, num2: #{num2}")
    m = build_map(word1, num1)
    # Logger.info("translate result: #{translate(num2, m)}")
    translate(num2, m) == word2
  end

  def build_map(word, num), do: bm(word |> to_charlist, num |> int2list, %{})
  defp bm([], [], acc), do: acc
  defp bm([h|t], [h1|t1], acc), do: bm(t, t1, Map.update(acc, h1, h, &(&1)))

  def translate(num, map), do: num |> int2list |> Enum.reduce([], fn x, acc -> [Map.fetch!(map, x)|acc] end) |> Enum.reverse() |> List.to_string

  def int2list(num), do: i2l(num, [])
  defp i2l(0, acc), do: acc
  defp i2l(num, acc), do: i2l(num |> div(10), [num |> rem(10)|acc])

  def pow(a, b), do: :math.pow(a, b) |> round()

  def generate_square(word1, word2) do
    l = String.length(word1)
    Logger.info("left: #{pow(10, l-1)}, right: #{pow(10, l)}")
    gsq(4, []) |> Enum.filter(fn x -> x > pow(10, l-1) and x < pow(10, l) end)
    |> map_by_digit |> Map.values
    |> Enum.filter(fn x -> length(x) > 1 end)
    |> Enum.filter(fn x -> not (x |> List.first |> repeat_digit?()) end)
    |> Enum.reduce([], fn x, acc -> acc ++ (x |> choose(2)) end)
    |> Enum.filter(fn x -> word_match?([word1, word2], x) end)
  end
  defp gsq(index, acc) when index * index > @limit, do: acc |> Enum.reverse
  defp gsq(index, acc), do: gsq(index+1, [index * index|acc])

  def get_key(word), do: word |> String.to_charlist |> Enum.sort() |> Enum.join("")
  def get_num_key(num), do: num |> int2list |> Enum.sort() |> Enum.join("")

  @doc """
  ## Example

      iex> Generator.choose([1,2,3], 2)
      [[1, 2], [1, 3], [2, 3]]
  """
  @spec choose(List, Integer) :: List
  def choose(lst, n), do: chs(lst, n) |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end) |> MapSet.to_list()
  defp chs(lst, n) when length(lst) == n, do: [lst]
  defp chs(lst, 1), do: lst |> Enum.map(fn x -> [x] end)
  defp chs([h|t], n), do: (choose(t, n-1) |> Enum.map(fn x -> [h|x] end)) ++ choose(t, n)

  def map_by_charactor(list), do: mbc(list, %{})
  defp mbc([], acc), do: acc
  defp mbc([h|t], acc) do
    s = h |> get_key
    case Map.fetch(acc, s) do
      :error -> mbc(t, Map.update(acc, s, [h], &(&1)))
      {:ok, v} -> mbc(t, Map.update(acc, s, [], fn _ -> [h|v] end))
    end
  end

  def repeat_digit?(num) do
    lst = num |> int2list()
    l = lst |> Enum.sort() |> Enum.dedup() |> length
    l != length(lst)
  end

  def map_by_digit(list), do: mbd(list, %{})
  defp mbd([], acc), do: acc
  defp mbd([h|t], acc) do
    s = h |> get_num_key
    case Map.fetch(acc, s) do
      :error -> mbd(t, Map.update(acc, s, [h], &(&1)))
      {:ok, v} -> mbd(t, Map.update(acc, s, [], fn _ -> [h|v] end))
    end
  end

end
