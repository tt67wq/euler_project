defmodule Buckets do
  @moduledoc """
  将n个元素丢进m个桶里面，m个桶最终每个桶里的个数集合
  x1+x2+...+xm = n
  {x1, x2, .... xn}个数
  """
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
  
end
