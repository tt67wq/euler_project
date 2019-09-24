defmodule CountingSummations do
  @moduledoc """
  https://projecteuler.net/problem=76
  思路：
  采用递归，每次递归采用从小到大的排序
  """
  use GenServer
  require Logger

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

  def multi(a, b), do: a * b
  def add(a, b), do: a + b

  def divide_into(m, 2, from), do: div(m, 2) - from + 1
  def divide_into(m, n, from), do: di(m, n, from, div(m, n), 0)
  defp di(_m, _n, index, to, acc) when index > to, do: acc
  defp di(m, n, index, to, acc) do
    di(m, n, index + 1, to, acc + cache_divide_into(m - index, n - 1, index))
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

  def divide_sum(m, n), do: divide_into(m, n, 1)

  def solution(m) do
    start_link()
    2..m |> Enum.reduce(0, fn x, acc -> divide_sum(m, x) |> add(acc) end)
  end
end
