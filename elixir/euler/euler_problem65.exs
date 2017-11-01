defmodule ConvergentsOfE do
  @moduledoc """
  https://projecteuler.net/problem=65
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

  @doc """
  e的第N个分解数字
  """
  def e_fraction(n) do
    m = rem(n, 3)
    d = div(n, 3)
    case m do
      2 -> (d + 1) * 2
      _ -> 1
    end
  end

  @doc """
  计算第N个逼近分数的分子和分母
  """
  @spec convergent(Integer) :: Tuple
  def convergent(0), do: {2, 1}
  def convergent(1), do: {3, 1}
  def convergent(n) do
    {a1, b1} = cache_convergent(n - 1)
    {a2, b2} = cache_convergent(n - 2)	
    m = rem(n, 3)
    case m do
      2 ->
	e = e_fraction(n)
	{e * a1 + a2, e * b1 + b2}
      _ ->
	{a1 + a2, b1 + b2}
    end
  end

  def cache_convergent(n) do
    v = get(:e, n)
    case v do
      nil ->
	v = convergent(n)
	set(:e, n, v)
	v
      _ -> v
    end
  end

  def digit_sum(n), do: ds(n, 0)
  defp ds(0, acc), do: acc
  defp ds(n, acc), do: ds(div(n, 10), acc + rem(n, 10))


  def solution() do
    start_link()
    {a, _} = convergent(99)
    digit_sum(a)
  end



end
