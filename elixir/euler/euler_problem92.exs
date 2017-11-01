defmodule SquareDigitChains do
  @moduledoc """
  https://projecteuler.net/problem=92
  """
  @limit 10000000

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


  def iter(num), do: iter(num, 0)
  defp iter(0, acc), do: acc
  defp iter(num, acc), do: iter(div(num, 10), acc + rem(num, 10) * rem(num, 10))

  def loop_at(1), do: 1
  def loop_at(89), do: 89
  def loop_at(num), do: cache_loop_at(iter(num))

  def cache_loop_at(num) do
    v = get(:loop, num)
    case v do
      nil ->
	value = loop_at(num)
	set_and_get(:loop, num, value)
      _ -> v
    end
  end


  def solution do
    start_link()
    1..@limit |> Enum.filter(fn x -> cache_loop_at(x) == 89 end)
    |> length()
  end

  
end
