defmodule XORDecryption do
  @moduledoc """
  https://projecteuler.net/problem=59
  """
  require Bitwise

  @letters [
    "a",
    "b",
    "c",
    "d",
    "e",
    "f",
    "g",
    "h",
    "i",
    "j",
    "k",
    "l",
    "m",
    "n",
    "o",
    "p",
    "q",
    "r",
    "s",
    "t",
    "u",
    "v",
    "w",
    "x",
    "y",
    "z"
  ]

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

  defp de([h1 | t1], [h2 | t2], acc) do
    de(t1, t2, [xor(h1, h2) | acc])
  end

  @spec now() :: integer()
  def now(), do: :os.system_time(:milli_seconds)

  def solution() do
    start = now()
    {_, content} = File.read("cipher.txt")

    cipher =
      content
      |> String.replace("\n", "")
      |> String.split(",")
      |> Enum.map(fn x -> String.to_integer(x) end)

    [{_, plaintext}] =
      all_possible_keys()
      |> Stream.map(fn x -> {x, decryption(cipher, x)} end)
      |> Stream.filter(fn {_, x} -> not String.contains?(x, "&") end)
      |> Stream.filter(fn {_, x} -> not String.contains?(x, "*") end)
      |> Stream.filter(fn {_, x} -> not String.contains?(x, "|") end)
      |> Stream.filter(fn {_, x} -> not String.contains?(x, "~") end)
      |> Stream.filter(fn {_, x} -> not String.contains?(x, "\\") end)
      |> Stream.filter(fn {_, x} -> not String.contains?(x, "{") end)
      |> Stream.filter(fn {_, x} -> not String.contains?(x, "#") end)
      |> Enum.to_list()

    IO.puts(plaintext)

    res =
      plaintext
      |> String.split("", trim: true)
      |> Enum.map(fn x -> ascii(x) end)
      |> Enum.sum()

    IO.puts(res)

    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
