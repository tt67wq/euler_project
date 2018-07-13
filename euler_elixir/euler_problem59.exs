defmodule XORDecryption do
  @moduledoc """
  https://projecteuler.net/problem=59
  """
  require Bitwise

  @letters ["a", "b", "c", "d", "e", "f", "g",
	    "h", "i", "j", "k", "l", "m", "n",
	    "o", "p", "q", "r", "s", "t",
	    "u", "v", "w", "x", "y", "z"]

  @doc """
  计算字母的Ascii码值
  ## Example

      iex> ascii("A")
      65
  """
  def ascii(letter), do: letter |> to_charlist() |> List.first()

  @doc """
  异或运算
  ## Example

      iex> xor(65, 42)
      107
  """
  def xor(a, b), do: Bitwise.bxor(a, b)

  @doc """
  所有可能的密钥
  """
  def all_possible_keys() do
    for x <- @letters,
      y <- @letters,
      z <- @letters do
	[x, y, z] |> Enum.map(fn x -> ascii(x) end)
    end
  end

  @doc """
  将列表循环重复至大于某长度
  ## Example

      iex> repeat_to_length([1,2,3], 10)
      [1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3]

  """
  def repeat_to_length(lst, len) do
    d = div(len, length(lst)) + 1
    List.duplicate(lst, d) |> List.flatten()
  end


  def decryption(ciphertext, key) do
    pkey = repeat_to_length(key, length(ciphertext))
    de(ciphertext, pkey, [])
  end

  defp de([], _, acc), do: List.to_string(acc |> Enum.reverse())
  defp de([h1|t1], [h2|t2], acc) do
    de(t1, t2, [xor(h1, h2)|acc])
  end

  def solution() do
    {_, content} = File.read("cipher.txt")
    cipher = content |> String.replace("\n", "")
    |> String.split(",")
    |> Enum.map(fn x -> String.to_integer(x) end)
    all_possible_keys() |> Stream.map(fn x -> {x, decryption(cipher, x)} end)
    |> Stream.filter(fn {_ ,x} -> not String.contains?(x, "&") end)
    |> Stream.filter(fn {_ ,x} -> not String.contains?(x, "*") end)
    |> Stream.filter(fn {_ ,x} -> not String.contains?(x, "|") end)
    |> Stream.filter(fn {_ ,x} -> not String.contains?(x, "~") end)
    |> Stream.filter(fn {_ ,x} -> not String.contains?(x, "\\") end)
    |> Stream.filter(fn {_ ,x} -> not String.contains?(x, "{") end)
    |> Stream.filter(fn {_ ,x} -> not String.contains?(x, "#") end)
    |> Enum.to_list()
  end

  @doc """
  按既有顺序合并两个list
  ## Example

      iex> PasscodeDerivation.merge_list([3,1,9],[6, 8, 0])
      [[6, 8, 0, 3, 1, 9], [6, 8, 3, 0, 1, 9], [6, 8, 3, 1, 0, 9], [6, 8, 3, 1, 9, 0],
      [6, 3, 8, 0, 1, 9], [6, 3, 8, 1, 0, 9], [6, 3, 8, 1, 9, 0], [6, 3, 1, 8, 0, 9],
      [6, 3, 1, 8, 9, 0], [6, 3, 1, 9, 8, 0], [3, 6, 8, 0, 1, 9], [3, 6, 8, 1, 0, 9],
      [3, 6, 8, 1, 9, 0], [3, 6, 1, 8, 0, 9], [3, 6, 1, 8, 9, 0], [3, 6, 1, 9, 8, 0],
      [3, 1, 6, 8, 0, 9], [3, 1, 6, 8, 9, 0], [3, 1, 6, 9, 8, 0], [3, 1, 9, 6, 8, 0]]
  """
  def merge_list(list1, list2) do
    l1 = length(list1)
    l2 = length(list2)
    List.duplicate(1, l1) ++ List.duplicate(0, l2)
    |> arrange()
    |> Enum.map(fn x -> ml(list1, list2, x, []) end)
  end


end
