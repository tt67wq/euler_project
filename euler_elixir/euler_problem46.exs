defmodule GoldbachOtherConjecture do
  @moduledoc """
  It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

  9 = 7 + 2×12
  15 = 7 + 2×22
  21 = 3 + 2×32
  25 = 7 + 2×32
  27 = 19 + 2×22
  33 = 31 + 2×12

  It turns out that the conjecture was false.

  What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
  """

  require Integer
  
  @spec prime?(Integer) :: boolean
  def prime?(2), do: true
  def prime?(x), do: _is_prime(x, 2)
  defp _is_prime(x, i) when i > div(x, 2), do: true
  defp _is_prime(x, i) do
    case rem(x, i) do
      0 -> false
      _ -> _is_prime(x, i+1)
    end
  end

  @spec satisfy?(Integer) :: boolean
  def satisfy?(n), do: satisfy(n, 2)
  defp satisfy(n, index) do
    x = n - index * index * 2
    cond do
      x < 0 -> false
      prime?(x) -> true
      :else -> satisfy(n, index+1)
    end
  end


  @spec find(Integer) :: List
  def find(x) do
    9..x
    |> Stream.filter(fn x -> Integer.is_odd(x) end)
    |> Stream.filter(fn x -> not prime?(x) end)
    |> Stream.filter(fn x -> not satisfy?(x) end)
    |> Enum.to_list()
  end

  
end
