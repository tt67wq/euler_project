defmodule Prime do
  @moduledoc """
  Documentation for Prime.
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
  求前N个质数的和
  """
  @spec sum_primes(Integer) :: Integer
  def sum_primes(0), do: 0
  def sum_primes(n), do: sp(n, 3, 1, 2)
  defp sp(n, _index, count, acc) when count == n, do: acc
  defp sp(n, index, count, acc) do
    cond do
      cache_prime?(index) -> sp(n, index+2, count+1, acc + index)
      :else -> sp(n, index+2, count, acc)
    end
  end

  @doc """
  缓存过的质数和求值
  """
  @spec cache_sum_primes(Integer) :: Integer
  def cache_sum_primes(n) do
    cached_value = get(:sum_prime, n)
    case cached_value do
      nil ->
	value = sum_primes(n)
	set(:sum_prime, n, value)
	value
      _ -> cached_value
    end
  end

  @doc """
  质因数分解
  """
  @spec factorization(integer) :: map
  def factorization(n), do: fac(n, 2, [])
  defp fac(n, index, acc) when index * index > n and n > 1, do: list2map([n | acc])
  defp fac(n, index, acc) do
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

  @doc """
  获取num的因数个数
  """
  def get_fac_num(num) do
    num |> factorization
    |> Map.values
    |> Enum.reduce(1, fn x, acc -> acc * (x + 1) end)
  end

end
