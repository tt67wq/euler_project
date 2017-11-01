defmodule PrimePairSets do
  @moduledoc """
  The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating them in any order the result will always be prime.
  For example, taking 7 and 109, both 7109 and 1097 are prime. The sum of these four primes, 792, represents the lowest sum for a set of four primes with this property.

  Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.
  """
  require Integer
  require Logger
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
  
  @doc """
  质数检查
  """
  @spec prime?(Integer) :: boolean
  def prime?(2), do: true
  def prime?(3), do: true
  def prime?(x) do
    cond do
      Integer.is_even(x) -> false
      :else -> _is_prime(x, 5)
    end
  end
  defp _is_prime(x, i) when i > div(x, 2), do: true
  defp _is_prime(x, i) do
    v = rem(x, 6)
    cond do
      v != 1 and v != 5 -> false
      rem(x, i) == 0 or rem(x, i+2) == 0 -> false
      :else -> _is_prime(x, i+6)
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
  获得一个数字的长度
  """
  def num_length(x), do: nl(x, 1)
  defp nl(0, acc), do: acc
  defp nl(x, acc), do: nl(div(x, 10), acc * 10)

  @doc """
  是否是成对为素数
  """
  @spec pair_prime?(Integer, Integer) :: boolean
  def pair_prime?(a, b), do: prime?(a * num_length(b) + b) and prime?(b * num_length(a) + a)

  @doc """
  ## Example

      iex> Generator.choose([1,2,3], 2)
      [[1, 2], [1, 3], [2, 3]]
  """
  @spec choose(List, Integer) :: List
  def choose(lst, n) when length(lst) == n, do: [lst]
  def choose(lst, 1), do: lst |> Enum.map(fn x -> [x] end)
  def choose([h|t], n), do: (choose(t, n-1) |> Enum.map(fn x -> [h|x] end)) ++ choose(t, n)


  @doc """
  列表内数字是否两两链接为素数
  """
  @spec list_pair_prime?(List) :: boolean
  def list_pair_prime?(lst) do
    case length(lst) do
      0 -> true
      1 -> true
      _ ->
	t = choose(lst, 2) |> Enum.filter(fn [a, b] -> not pair_prime?(a, b) end)
	length(t) == 0
    end
  end

  def pair_select(a, plist), do: plist |> Enum.filter(fn x -> pair_prime?(a, x) end)

  def solution(limit) do
    plist = 2..2000 |> Enum.map(fn x -> cache_n_prime(x) end)
    sl(plist, limit)
  end

  defp sl([], 0), do: []
  defp sl([h|_t], 0), do: [h]
  defp sl([], limit) when limit > 0, do: []
  defp sl([h|t], limit) do
    cond do
      length([h|t]) < limit -> []
      :else ->
	p = pair_select(h, t)
	Logger.info("limit: #{limit}")
	Logger.info("p: #{inspect p}")
	acc = sl(p, limit-1)
	Logger.info("#{inspect acc}")
	cond do
	  acc == [] -> sl(t, limit)
	  [h|acc] |> list_pair_prime?() -> [h|acc]
	  :else -> sl(t, limit)
	end
    end
  end
end
