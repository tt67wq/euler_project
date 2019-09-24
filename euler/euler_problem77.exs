defmodule PrimeSummations do
  @moduledoc """
  https://projecteuler.net/problem=77
  """
  require Logger
  require Integer
  use GenServer

  # --------------------- 质数与缓存工具 -------------------------
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
  # --------------------- 质数与缓存工具 -------------------------

  def add(a, b), do: a + b
  @doc """
  将m分解成n个质数和一共有多少种可能
  ## Example

      iex> 

  """
  def divide_into(m, 2, from) do
    from..div(m, 2) |> Enum.filter(fn x -> cache_prime?(x) and cache_prime?(m-x) end) |> length()
  end

  def divide_into(m, n, from), do: di(m, n, from, div(m, n), 0)
  defp di(_m, _n, index, to, acc) when index > to, do: acc
  defp di(m, n, index, to, acc) do
    cond do
      cache_prime?(index) ->
	di(m, n, next_prime(index), to, cache_divide_into(m - index, n - 1, index) + acc)
      :else -> di(m, n, next_prime(index), to, acc)
    end
  end

  def cache_divide_into(m, n, f) do
    d = get(:d, {m, n, f})
    case d do
      nil ->
	nd = divide_into(m, n, f)
	set(:d, {m, n, f}, nd)
	nd
      _ -> d
    end
  end

  def divide_sum(m, n), do: divide_into(m, n, 2)

  def all_divide_sum(m), do: 2..div(m, 2) |> Enum.reduce(0, fn x, acc -> divide_sum(m, x) |> add(acc) end)
  
  def solution(limit) do
    start_link()
    sl(limit, 10)
  end

  defp sl(limit, index) do
    cond do
      all_divide_sum(index) > limit -> index
      :else -> sl(limit, index + 1)
    end
  end
end
