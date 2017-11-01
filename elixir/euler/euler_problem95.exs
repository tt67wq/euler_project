defmodule AmicableChains do
  @moduledoc """
  https://projecteuler.net/problem=95
  """
  @limit 1000000

  require Logger
  require Integer
  use GenServer

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

  def handle_cast({:drop, tag, keys}, state) do
    case Map.fetch(state, tag) do
      {:ok, mc} ->
	{:noreply, Map.update!(state, tag, fn _ -> Map.drop(mc, keys) end)}
      :error ->
	{:noreply, state}
    end
  end

  ### Client
  def start_link(state \\ %{}) do
    GenServer.start_link(__MODULE__, state, name: __MODULE__)
  end

  def get(tag, key), do: GenServer.call(__MODULE__, {:get, tag, key})
  def set(tag, key, value), do: GenServer.cast(__MODULE__, {:set, tag, key, value})
  def drop(tag, keys), do: GenServer.cast(__MODULE__, {:drop, tag, keys})
  def set_and_get(tag, key, value) do
    set(tag, key, value)
    value
  end


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



  def factorization(n), do: fac(n, 2, [])
  defp fac(n, index, acc) when index * index > n and n > 1, do: [n | acc]
  defp fac(n, index, acc) do
    case rem(n, index) == 0 do
      true -> fac(div(n, index), index, [index | acc])
      _ -> fac(n, index + 1, acc)
    end
  end

  @doc """
  ## Example

      iex> Generator.choose([1,2,3], 2)
      [[1, 2], [1, 3], [2, 3]]
  """
  @spec choose(List, Integer) :: List
  def choose(lst, n), do: chs(lst, n) |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end) |> MapSet.to_list()
  defp chs(lst, n) when length(lst) == n, do: [lst]
  defp chs(lst, 1), do: lst |> Enum.map(fn x -> [x] end)
  defp chs([h|t], n), do: (choose(t, n-1) |> Enum.map(fn x -> [h|x] end)) ++ choose(t, n)


  def product(list), do: list |> Enum.reduce(1, fn x, acc -> x * acc end)
  def add(a, b), do: a + b

  def proper_divisors_sum(1), do: 1
  def proper_divisors_sum(num) do
    facs = factorization(num)
    case length(facs) do
      1 -> 1
      _ ->
	1..length(facs)-1 |> Enum.map(fn x -> choose(facs, x) end)
	|> Enum.map(fn x -> x |> Enum.map(fn x -> product(x) end) end)
	|> List.flatten
	|> Enum.sum
	|> add(1)
    end
  end

  def cache_proper_divisors_sum(num) do
    v = get(:ps, num)
    case v do
      nil ->
	v = proper_divisors_sum(num)
	set_and_get(:ps, num, v)
      _ -> v
    end
  end


  def get_ps_chain(num), do: gpc(num, num, [])
  defp gpc(init, num, acc) do
    next = cache_proper_divisors_sum(num)
    cond do
      next > @limit -> []
      cache_prime?(next) -> []
      Enum.member?(acc, next) ->
	cond do
	  next == init -> [num|acc]
	  :else -> []
	end
      :else -> gpc(init, next, [num|acc])
    end
  end

  def solution() do
    start_link()
    sl(1, 0, [])
  end

  def exceed_limit?(list) do
    l = list |> Enum.filter(fn x -> x > @limit end) |> length
    l > 0
  end


  defp sl(index, l, acc) when index > @limit, do: {l, acc}
  defp sl(index, l, acc) do
    chain = get_ps_chain(index)
    len = chain |> length
    # Logger.info("#{index}: #{inspect chain}")
    cond do
      len > l ->
	Logger.info("#{index}: #{inspect chain}")
	cond do
	  exceed_limit?(chain) -> sl(index+1, l, acc)
	  :else -> sl(index+1, len, {index, chain})
	end
      :else -> sl(index+1, l, acc)
    end
  end
end
