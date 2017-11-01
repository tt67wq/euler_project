defmodule CoinPartitions do
  @moduledoc """
  https://projecteuler.net/problem=78
  """

  use GenServer
  require Logger
  require Time

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


  def multi(a, b), do: a * b
  def add(a, b), do: a + b
  def sub(a, b), do: b - a

  @doc """
  广义五边形数字
  ## Example

      iex> five_number(7)
      15

  """
  def five_number(n) do
    case rem(n, 2) do
      1 ->
	k = div(n, 2)
	k |> multi(k)
	|> multi(3)
	|> add(k)
	|> div(2)
      0 ->
	k = div(n, 2)
	k |> multi(k)
	|> multi(3)
	|> add(0 - k)
	|> div(2)
    end
  end

  def cache_five_number(n) do
    case get(:five, n) do
      nil -> set_and_get(:five, n, five_number(n))
      _ -> get(:five, n)
    end

  end


  @doc """
  整数拆分的递归
  ## Example

  iex> 

  """
  def p(0), do: 1
  def p(1), do: 1
  def p(2), do: 2
  def p(n), do: p(n, 2, 0)
  defp p(n, index, acc) do
    cond do
      cache_five_number(index) > n -> acc
      :else ->
	case rem(index, 4) do
	  2 -> p(n, index + 1, cache_p(n - cache_five_number(index)) + acc)
	  3 -> p(n, index + 1, cache_p(n - cache_five_number(index)) + acc)
	  0 -> p(n, index + 1, acc - cache_p(n - cache_five_number(index)))
	  1 -> p(n, index + 1, acc - cache_p(n - cache_five_number(index)))
	end
    end
  end

  def cache_p(n) do
    case get(:p, n) do
      nil -> set_and_get(:p, n, p(n))
      _ -> get(:p, n)
    end
  end

  def solution(m) do
    start_link()
    sl(m, 1)
  end

  defp sl(m, index) do
    p = cache_p(index, m)
    Logger.info("p(#{index}): #{p}")
    case p do
      0 -> index
      _ -> sl(m, index + 1)
    end
  end



  
end
