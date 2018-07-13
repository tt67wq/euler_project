defmodule TotientPermutation do
  @moduledoc """
  https://projecteuler.net/problem=70
  根据69题的思路，要n/phi(n)最小，即要求n的质因数最少
  该问题即转换为寻找phi为自身重排列，且质因数最少的数字
  质数的质因数只有本身，但是质数的phi为本身-1，不能为本身的重排列
  可以先考虑质因数个数为2的数字, 即为两个质数的积
  """
  require Logger
  require Integer
  use GenServer

  # 多路缓存
  ### GenServer API
  def init(state), do: {:ok, state}

  def handle_call({:get, tag, key}, _from, state) do
    case Map.fetch(state, tag) do
      {:ok, mc} ->
	case Map.fetch(mc, key) do
	  {:ok, value} -> {:reply, value, state}
	  :error -> {:reply, nil, state}
	end
      :error -> {:reply, nil, state}
    end
  end

  def handle_cast({:set, tag, key, value}, state) do
    case Map.fetch(state, tag) do
      {:ok, mc} ->
	{:noreply, Map.update!(state, tag, fn _ -> Map.put(mc, key, value) end)}
      :error ->
	{:noreply, Map.put(state, tag, %{key => value})}
    end
  end

  ### Client
  def start_link(state \\ %{}) do
    GenServer.start_link(__MODULE__, state, name: __MODULE__)
  end

  def get(tag, key), do: GenServer.call(__MODULE__, {:get, tag, key})
  def set(tag, key, value), do: GenServer.cast(__MODULE__, {:set, tag, key, value})

  @doc """
  质数检查
  """
  @spec prime?(Integer) :: boolean
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
    cached_value = get(:prime, x)
    case cached_value do
      nil ->
	value = prime?(x)
	set(:prime, x, value)
	value
      _ -> cached_value
    end
  end

  @doc """
  找到第N个质数
  """
  @spec n_prime(Integer) :: Integer
  def n_prime(1), do: 2
  def n_prime(n), do: np(n, 1, 2)
  defp np(n, index, acc) when index == n, do: acc
  defp np(n, index, acc) when index < n, do: np(n, index+1, next_prime(acc))

  def cache_n_prime(n) do
    cached_value = get(:n_prime, n)
    case cached_value do
      nil ->
	value = n_prime(n)
	set(:n_prime, n, value)
	value
      _ -> cached_value
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

  def list2map(lst), do: list2map(lst, %{})
  defp list2map([], acc), do: acc
  defp list2map([h|t], acc) do
    case Map.fetch(acc, h) do
      {:ok, c} -> list2map(t, Map.update(acc, h, c, &(&1 + 1)))
      :error -> list2map(t, Map.update(acc, h, 1, &(&1 + 1)))
    end
  end

  def phi(n) do
    cond do
      cache_prime?(n) -> n - 1
      :else -> factorization(n) |> Map.keys() |> Enum.reduce(n, fn x, acc -> acc * (1 - 1 / x) end) |> round()
    end
  end


  @doc """

  ## Example
  
      iex>?> Generator.arrange([1, 2, 3])
      [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
  """
  @spec arrange(List) :: List
  def arrange(lst) when length(lst) == 1, do: [lst]
  def arrange([h|t]), do: arrange(t) |> Enum.reduce([], fn x, acc -> insert(h, x) ++ acc end)
  def insert(n, lst), do: 0..length(lst) |> Enum.map(fn x -> List.insert_at(lst, x, n) end)

  @doc """
  检查数字b是否为数字a的一个重排列
  """
  def permutation?(a, b) do
    c = Integer.to_charlist(a) |> Enum.sort()
    c == Integer.to_charlist(b) |> Enum.sort()
  end

  def solution(limit) do
    start_link()
    cache_n_prime(600)
    sl(limit, 1, 1, {4, 2})
  end
  defp sl(_limit, i, _j, acc) when i >= 600, do: acc
  defp sl(limit, i, j, acc) when j >= i, do: sl(limit, i+1, 1, acc)
  defp sl(limit, i, j, {_, d}=acc) do
    pi = cache_n_prime(i)
    pj = cache_n_prime(j)
    cond do
      pi * pj > limit -> sl(limit, i+1, 1, acc)
      permutation?(pi * pj, (pi-1)*(pj-1)) ->
	Logger.info("#{pi} * #{pj} 的phi为自身的全排列")
	nd = (pi * pj) / ((pi - 1) * (pj - 1))
	cond do
	  nd < d -> sl(limit, i, j+1, {pi * pj, nd})
	  :else -> sl(limit, i, j+1, acc)
	end
      :else -> sl(limit, i, j+1, acc)
    end
  end
end
