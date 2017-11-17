defmodule CountingBlockCombinationsI do
  @moduledoc """
  https://projecteuler.net/problem=114
  """
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
  def set_and_get(tag, key, value) do
    set(tag, key, value)
    value
  end

  def add2list(list, _, 0), do: list
  def add2list(list, k, n), do: add2list([k|list], k, n-1)

  def cache_combine(x) do
    v = get(:c, x)
    case v do
      nil -> set_and_get(:c, x, combine(x))
      _ -> v
    end
  end


  # def combine(n) when n <= 0, do: [[]]
  # def combine(1), do: [[0]]
  # def combine(2), do: [[0, 0]]
  # def combine(3), do: [[0, 0, 0], [1, 1, 1]]
  # def combine(4), do: [[0, 0, 0, 0], [0, 1, 1, 1], [1, 1, 1, 0], [1, 1, 1, 1]]
  # def combine(5), do: (combine(4) |> Enum.map(fn x -> [0|x] end)) ++ [[1,1,1,0,0],[1,1,1,1,0],[1,1,1,1,1]]
  # def combine(n), do: (cache_combine(n-1) |> Enum.map(fn x -> [0|x] end)) ++ combine(n, 3, [])
  # defp combine(n, index, acc) when index > n, do: acc
  # defp combine(n, n, acc), do: [1..n |> Enum.map(fn _ -> 1 end)|acc]
  # defp combine(n, index, acc), do: combine(n, index+1, (cache_combine(n-index-1) |> Enum.map(fn x -> add2list([0|x], 1, index) end)) ++ acc)

  def combine(n) when n <= 2, do: 1
  def combine(3), do: 2
  def combine(4), do: 4
  def combine(5), do: 7
  def combine(n), do: cache_combine(n-1) + combine(n, 3, 0)
  defp combine(n, index, acc) when index > n, do: acc
  defp combine(n, n, acc), do: acc + 1
  defp combine(n, index, acc), do: combine(n, index+1, cache_combine(n-index-1) + acc)

  def solution(), do: combine(50)
end
