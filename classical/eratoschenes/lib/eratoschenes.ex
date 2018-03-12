defmodule Eratoschenes do
  alias Eratoschenes.Cache
  require Integer

  @moduledoc """
  Documentation for Eratoschenes.
  """

  @spec prime?(Integer) :: boolean
  def prime?(1), do: false
  def prime?(2), do: true
  def prime?(3), do: true

  def prime?(x) do
    cond do
      Integer.is_even(x) -> false
      :else -> is_prime(x, 3)
    end
  end

  defp is_prime(x, c) when c * c > x, do: true

  defp is_prime(x, c) do
    cond do
      rem(x, c) == 0 -> false
      :else -> is_prime(x, next_prime(c))
    end
  end

  @doc """
  获得下一个质数
  """
  def next_prime(2), do: 3

  def next_prime(x) do
    cond do
      Integer.is_even(x) -> np(x + 1)
      :else -> np(x + 2)
    end
  end

  defp np(y) do
    cond do
      cache_prime?(y) -> y
      :else -> np(y + 2)
    end
  end

  @doc """
  缓存的质数判断
  """
  def cache_prime?(x) do
    cached_value = Cache.get(:prime, x)

    case cached_value do
      nil -> Cache.set_and_get(:prime, x, prime?(x))
      _ -> cached_value
    end
  end

  @doc """
  获得小于n的所有素数
  """
  def get_primes_before(n) do
    data = 1..n |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, x, true) end)
    root = :math.sqrt(n) |> round()

    2..root
    |> Enum.filter(fn x -> cache_prime?(x) end)
    |> Enum.reduce(data, fn x, acc -> filtrate(2 * x, x, n, acc) end)
    |> Map.to_list()
    |> Enum.filter(fn {_, x} -> x end)
    |> Enum.map(fn {x, _} -> x end)
  end

  defp filtrate(index, _p, n, data) when index > n, do: data
  defp filtrate(index, p, n, data), do: filtrate(index + p, p, n, Map.put(data, index, false))
end
