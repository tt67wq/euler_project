defmodule QuadraticPrimes do
  @moduledoc """
  https://projecteuler.net/problem=27
  """

  # 以下为素数工具
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
  def prime?(1), do: false
  def prime?(2), do: true
  def prime?(3), do: true
  def prime?(x) do
    cond do
      x < 0 -> prime?(0 - x)
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
  def next_prime(-3), do: -2
  def next_prime(-2), do: 2
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

  # 以下为本题的逻辑
  def formula(n, a, b), do: n * n + a * n + b
  def prime_num_of_formula(a, b), do: pn(a, b, 1)
  defp pn(a, b, index) do
    p? = formula(index, a, b) |> cache_prime?()
    case p? do
      false -> index-1
      true -> pn(a, b, index+1)
    end
  end

  def solution() do
    start_link()
    sl(0, -999, {0, 0, 0})
  end

  defp sl(a, _b, acc) when a > 999, do: acc
  defp sl(a, b, acc) when b > 999, do: sl(a + 1, -999, acc)
  defp sl(a, b, {_, _, p}=acc) do
    Logger.info("#{a}, #{b}, #{inspect acc}")
    c = a + b + 1
    case cache_prime?(c) do
      true ->
	pn = prime_num_of_formula(a, b)
	cond do
	  pn > p -> sl(a, next_prime(b), {a, b, pn})
	  :else -> sl(a, next_prime(b), acc)
	end
      false -> sl(a, next_prime(b), acc)
    end
  end
end
