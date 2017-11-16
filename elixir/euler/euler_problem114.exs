defmodule CountingBlockCombinationsI do
  @moduledoc """
  https://projecteuler.net/problem=114
  """
  require Logger
  @limit 7

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

  def factorial(n), do: fac(n, 1)
  defp fac(0, acc), do: acc
  defp fac(n, acc), do: fac(n-1, acc * n)

  def choose(n, x), do: div(factorial(n), factorial(x) * factorial(n-x))

  def generate_list(a, b), do: (1..a |> Enum.map(fn _ -> 0 end)) ++ (1..b |> Enum.map(fn _ -> 1 end))

  def pow(a, b), do: :math.pow(a, b) |> round()

  def bucket(0, _), do: 1
  def bucket(_, 1), do: 1
  def bucket(n, m), do: bucket(n, 0, m, 0)
  defp bucket(n, k, _m, acc) when k > n, do: acc
  defp bucket(n, k, m, acc), do: bucket(n, k+1, m, cache_bucket(n-k, m-1) + acc)

  def cache_bucket(a, b) do
    v = get(:bucket, {a, b})
    case v do
      nil -> set_and_get(:bucket, {a, b}, bucket(a, b))
      _ -> v
    end
  end

  def place_red_block_in_line(0, _), do: 1
  def place_red_block_in_line(@limit, 1), do: 1
  def place_red_block_in_line(l, n) when n * l > @limit, do: 0
  def place_red_block_in_line(l, 1), do: @limit - l + 1
  def place_red_block_in_line(l, n) do
    bs = @limit - l * n + n
    rest = bs - (n * 2 - 1)
    cache_bucket(rest, n * 2)
  end

  def add(a, b), do: a + b

  def solution() do
    start_link()
    sl(3, 1, place_red_block_in_line(3, 1), [])
    |> Enum.sum()
    |> add(1)
  end

  defp sl(_l, 1, 0, acc), do: acc
  defp sl(l, _, 0, acc), do: sl(l+1, 1, place_red_block_in_line(l+1, 1), acc)
  defp sl(l, c, n, acc) do
    Logger.info("l: #{l}, c: #{c}, n: #{n}")
    sl(l, c+1, place_red_block_in_line(l, c+1), [n|acc])
  end
end
