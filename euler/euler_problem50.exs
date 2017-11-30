defmodule ConsecutivePrimeSum do
  @moduledoc """
  The prime 41, can be written as the sum of six consecutive primes:

  41 = 2 + 3 + 5 + 7 + 11 + 13
  This is the longest sum of consecutive primes that adds to a prime below one-hundred.

  The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.

  Which prime, below one-million, can be written as the sum of the most consecutive primes?
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
  def prime?(x) do
    cond do
      Integer.is_even(x) -> false
      :else -> _is_prime(x, 2)
    end
  end
  defp _is_prime(x, i) when i > div(x, 2), do: true
  defp _is_prime(x, i) do
    case rem(x, i) do
      0 -> false
      _ -> _is_prime(x, i+1)
    end
  end

  @doc """
  找到第N个质数
  """
  @spec n_prime(Integer) :: Integer
  def n_prime(1), do: 2
  def n_prime(n), do: np(n, 3, 1, 2)
  defp np(n, _index, count, acc) when count == n, do: acc
  defp np(n, index, count, acc) do
    cond do
      cache_prime?(index) -> np(n, index+2, count+1, acc+index)
      :else -> np(n, index+2, count, acc)
    end
  end

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


  def solution(limit), do: sl(limit, 1, 0, {0, 0})
  defp sl(limit, i, _j, acc) when i == limit, do: acc
  defp sl(limit, i, j, acc) when i == j, do: sl(limit, i+1, 0, acc)
  defp sl(limit, i, j, acc) do
    cond do
      cache_n_prime(i) > limit -> acc
      :else ->
	d = cache_sum_primes(i) - cache_sum_primes(j)
	l = i - j
	cond do
	  d > limit -> sl(limit, i, j+1, acc)
	  cache_prime?(d) ->
	    {ml, _md} = acc
	    cond do
	      l > ml -> sl(limit, i+1, 0, {l, d})
	      :else -> sl(limit, i+1, 0, acc)
	    end
	  :else -> sl(limit, i, j+1, acc)
	end
    end
  end
end
