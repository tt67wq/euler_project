defmodule RedGreenOrBlueTiles do
  @moduledoc """
  https://projecteuler.net/problem=116
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

  def red(m) when m < 2, do: 0
  def red(2), do: 1
  def red(3), do: 2
  def red(m), do: cache_red(m-2) + 1 + cache_red(m-1)

  def cache_red(x) do
    v = get(:red, x)
    case v do
      nil -> set_and_get(:red, x, red(x))
      _ -> v
    end
  end

  def green(m) when m < 3, do: 0
  def green(3), do: 1
  def green(4), do: 2
  def green(m), do: cache_green(m-3) + 1 + cache_green(m-1)

  def cache_green(x) do
    v = get(:green, x)
    case v do
      nil -> set_and_get(:green, x, green(x))
      _ -> v
    end
  end

  def blue(m) when m < 4, do: 0
  def blue(4), do: 1
  def blue(5), do: 2
  def blue(m), do: cache_blue(m-4) + 1 + cache_blue(m-1)

  def cache_blue(x) do
    v = get(:blue, x)
    case v do
      nil -> set_and_get(:blue, x, blue(x))
      _ -> v
    end
  end

  def solution() do
    start_link()
    blue(50) + green(50) + red(50)
  end
end
