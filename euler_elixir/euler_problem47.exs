defmodule DistinctPrimesFactors do
  @moduledoc """
  The first two consecutive numbers to have two distinct prime factors are:

  14 = 2 × 7
  15 = 3 × 5

  The first three consecutive numbers to have three distinct prime factors are:

  644 = 2² × 7 × 23
  645 = 3 × 5 × 43
  646 = 2 × 17 × 19.

  Find the first four consecutive integers to have four distinct prime factors each. What is the first of these numbers?
  """

  @doc """
  是否是质数
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
  质因数分解
  """
  @spec factorization(integer) :: map
  def factorization(n), do: fac(n, 2, [])
  defp fac(n, index, acc) when index * index > n and n > 1 do
    # Logger.info("final: #{n}, #{index}")
    list2map([n | acc])
  end
  defp fac(n, index, acc) do
    # Logger.info("#{n}, #{index}")
    case rem(n, index) == 0 do
      true -> fac(div(n, index), index, [index | acc])
      _ -> fac(n, index + 1, acc)
    end
  end

  @doc """
  将list转换为map
  ## Example

      iex> list2map([2, 2, 3])
      %{2 => 2, 3 => 1}
  """
  @spec list2map(List) :: Map
  def list2map(lst), do: list2map(lst, %{})
  defp list2map([], acc), do: acc
  defp list2map([h|t], acc) do
    case Map.fetch(acc, h) do
      {:ok, c} -> list2map(t, Map.update(acc, h, c, &(&1 + 1)))
      :error -> list2map(t, Map.update(acc, h, 1, &(&1 + 1)))
    end
  end

  @doc """
  找到四个连续的有四个质因数的数字
  """
  def find(), do: find(647, [])
  defp find(_index, acc) when length(acc) == 4, do: acc
  defp find(index, acc) do
    size = factorization(index) |> Map.to_list() |> length()
    case size do
      4 -> find(index+1, [index|acc])
      _ -> find(index+1, [])
    end
  end

end
