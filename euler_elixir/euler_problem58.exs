defmodule SpiralPrimes do
  @moduledoc """
  Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.

  37 36 35 34 33 32 31
  38 17 16 15 14 13 30
  39 18  5  4  3 12 29
  40 19  6  1  2 11 28
  41 20  7  8  9 10 27
  42 21 22 23 24 25 26
  43 44 45 46 47 48 49

  It is interesting to note that the odd squares lie along the bottom right diagonal, but what is more interesting is that 8 out of the 13 numbers lying along both diagonals are prime; that is, a ratio of 8/13 ≈ 62%.

  If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed.
  If this process is continued, what is the side length of the square spiral for which the ratio of primes along both diagonals first falls below 10%?
  """
  require Integer
  require Logger
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


  def cache_get_layer_list(index) do
    value = get(:layer, index)
    case value do
      nil ->
	value = get_layer_list(index)
	set(:layer, index, value)
	drop(:layer, [index-2])
	value
      _ -> value
    end
  end

  @doc """
  获得第N层时候边角列表
  """
  @spec get_layer_list(Integer) :: List
  def get_layer_list(1), do: [1]
  def get_layer_list(index) do
    [ru|_t] = cache_get_layer_list(index - 1)
    nru = ru + (index - 1) * 8 - 6
    l = (index - 1) * 2 + 1
    [ nru, nru + (l - 1), nru + 2 * (l - 1), nru + 3 * (l - 1)]
  end

  def solution(), do: s(1, 5, 3)
  defp s(index, tcount, pcount) do
    Logger.info("#{index * 2 + 1}")
    ratio = pcount / tcount
    Logger.info(ratio)
    cond do
      ratio > 0.1 ->
	p = cache_get_layer_list(index+1) |> Enum.filter(fn x -> prime?(x) end) |> length()
	Logger.info(p)
	s(index + 1, tcount + 4, pcount + p)
      :else -> index * 2 + 1
    end
  end
end
