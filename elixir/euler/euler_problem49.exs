defmodule PrimePermutations do
  @moduledoc """
  The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, 
  is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit numbers are permutations of one another.
  There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property, but there is one other 4-digit increasing sequence.
  What 12-digit number do you form by concatenating the three terms in this sequence?
  """
  require Logger
  @doc """
  质数检查
  """
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


  @doc """
  ## Example

      iex> PrimePermutations.choose([1,2,3], 2)
      [[1, 2], [1, 3], [2, 3]]
  """
  @spec choose(List, Integer) :: List
  def choose(lst, n) when length(lst) == n, do: [lst]
  def choose(lst, 1), do: lst |> Enum.map(fn x -> [x] end)
  def choose([h|t], n), do: (choose(t, n-1) |> Enum.map(fn x -> [h|x] end)) ++ choose(t, n)

  @doc """

  ## Example
  
      iex> PrimePermutations.arrange([1, 2, 3])
      [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
  """
  @spec arrange(List) :: List
  def arrange(lst) when length(lst) == 1, do: [lst]
  def arrange([h|t]), do: arrange(t) |> Enum.reduce([], fn x, acc -> insert(h, x) ++ acc end)

  @doc """
  数字的全排序

  ## Example

      iex> PrimePermutations.arrange(1234)
      [1342, 3142, 3412, 3421, 1324, 3124, 3214, 3241, 1234, 2134, 2314, 2341, 1432, 4132, 4312, 4321, 1423, 4123, 4213, 4231, 1243, 2143, 2413, 2431]
  """
  @spec arrange(Integer) :: List
  def arrange(num), do: arrange(Integer.to_charlist(num)) |> Enum.map(fn x -> List.to_integer(x) end) |> Enum.reduce(MapSet.new, fn x, acc -> MapSet.put(acc, x) end) |> MapSet.to_list()

  @doc """
  全位置插入

  ## Example

      iex> PrimePermutations.insert(1, [2,3,4])
      [[1, 2, 3, 4], [2, 1, 3, 4], [2, 3, 1, 4], [2, 3, 4, 1]]
  """
  @spec insert(Integer, List) :: List
  def insert(n, lst), do: 0..length(lst) |> Enum.map(fn x -> List.insert_at(lst, x, n) end)


  @doc """
  判断是否为等差数列

  ## Example

      iex> PrimePermutations.arithmetic?([1, 5, 9, 13])
      true
      iex> PrimePermutations.arithmetic?([1, 5, 9, 14])
      false
  """
  @spec arithmetic?(List) :: boolean
  def arithmetic?(lst) when length(lst) < 3, do: false
  def arithmetic?([h1, h2 | _t]=lst), do: arithmetic?(lst, abs(h1 - h2))
  defp arithmetic?([_x], _acc), do: true
  defp arithmetic?([h|t], acc) do
    [h1|_t1] = t
    cond do
      abs(h-h1) == acc -> arithmetic?(t, acc)
      :else -> false
    end
  end



  @doc """
  解
  """
  def solution(), do: find(1001, [], [])
  defp find(9997, acc, _checked), do: acc
  defp find(index, acc, checked) do
    if prime?(index) do
      cond do
	Enum.member?(checked, index) -> find(index+2, acc, checked)
	:else ->
	  primes = arrange(index) |> Enum.filter(fn x -> prime?(x) end) |> Enum.filter(fn x -> x > 1000 end)
	  cond do
	    length(primes) < 3 -> find(index+2, acc, checked ++ primes)
	    :else ->
	      arithmetic_primes = primes |> choose(3) |> Enum.map(fn x -> Enum.sort(x) end) |> Enum.filter(fn x -> arithmetic?(x) end) 
	      if length(arithmetic_primes) > 0 do
		find(index+2, [arithmetic_primes|acc], checked ++ primes)
	      else
		find(index+2, acc, checked ++ primes)
	      end
	  end
      end
    else
      find(index+2, acc, checked)
    end
  end
end
