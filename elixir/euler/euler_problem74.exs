defmodule DigitFactorialChains do
  @moduledoc """
  https://projecteuler.net/problem=74
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

  def factorial_digit(n), do: fd(n, 0)
  defp fd(0, acc), do: acc
  defp fd(n, acc) do
    f = rem(n, 10) |> factorial()
    fd(div(n, 10), acc + f)
  end

  def cache_factorial_digit(n) do
    value = get(:factorial, n)
    case value do
      nil ->
	value = factorial_digit(n)
	set(:factorial, n, value)
	value
      _ -> value
    end
  end

  def factorial(0), do: 1
  def factorial(n), do: factorial(n, 1)
  defp factorial(1, acc), do: acc
  defp factorial(n, acc), do: factorial(n - 1, acc * n)

  def get_chain(n), do: get_chain(n, MapSet.new())
  defp get_chain(n, acc) do
    cond do
      MapSet.member?(acc, n) -> acc
      :else ->
	f = cache_factorial_digit(n)
	chain = get(:chain, n)
	case chain do
	  nil -> get_chain(f, MapSet.put(acc, n))
	  _ ->
	    chain = MapSet.union(acc, chain)
	    set(:chain, n, chain)
	    chain
	end
    end
  end

  def solution(limit) do
    start_link()
    sl(limit, 1, [])
  end
  defp sl(limit, index, acc) when index >= limit, do: acc
  defp sl(limit, index, acc) do
    t = index |> get_chain() |> MapSet.size()
    cond do
      t >= 60 ->
	Logger.info("#{index}, #{t}")
	sl(limit, index + 1, [t|acc])
      :else -> sl(limit, index + 1, acc)
    end
  end
end
