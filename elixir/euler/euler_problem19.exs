defmodule CountingSundays do
  @moduledoc """
  https://projecteuler.net/problem=19
  """

  @days %{
    4 => 30,
    6 => 30,
    9 => 30,
    11 => 30
  }

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

  def get_days(year, 2) do
    cond do
      leap?(year) -> 29
      :else -> 28
    end
  end

  def get_days(_, month) do
    case Map.fetch(@days, month) do
      {:ok, v} -> v
      :error -> 31
    end
  end


  def leap?(year) do
    case rem(year, 100) do
      0 -> case rem(year, 400) do
	     0 -> true
	     _ -> false
	   end
      _ -> case rem(year, 4) do
	     0 -> true
	     _ -> false
	   end
    end
  end

  def add(a, b), do: a + b

  def first_day_of_month(1900, 1), do: 1
  def first_day_of_month(year, 1) do
    d = cache_first_day_of_month(year-1, 12)
    get_days(year-1, 12)
    |> add(d)
    |> rem(7)
  end

  def first_day_of_month(year, month) do
    d = cache_first_day_of_month(year, month-1)
    get_days(year, month-1)
    |> add(d)
    |> rem(7)
  end


  def cache_first_day_of_month(year, month) do
    v = get(:day, {year, month})
    case v do
      nil ->
	v = first_day_of_month(year, month)
	set(:day, {year, month}, v)
	v
      _ -> v
    end
  end

  def solution() do
    start_link()
    sl()
    |> Enum.filter(fn {_, x} -> x == 0 end)
    |> length()
  end

  defp sl() do
    for year <- 1901..2000,
      month <- 1..12 do
	{{year, month}, cache_first_day_of_month(year, month)}
    end
  end
end
