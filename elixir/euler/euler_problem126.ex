defmodule CuboidLayers do
  @moduledoc """
  https://projecteuler.net/problem=126
  """

  @limit 154
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

  def cover_cube_nums(a, b, c, 1), do: {a * b + 2 * a + 2 * b, 2 * (a * b + b * c + c * a)}
  def cover_cube_nums(a, b, c, n) do
    {area, _} = cache_cover(a, b, c, n-1)
    {area + 2 * a + 2 * b + 4 * (n-1), 2 * area + c * (2 * a + 2 * b + 4 * (n-1))}
  end

  def cache_cover(a, b, c, n) do
    v = get(:cube, {a, b, c, n})
    case v do
      nil -> set_and_get(:cube, {a, b, c, n}, cover_cube_nums(a, b, c, n))
      _ -> v
    end
  end

  def solution() do
    start_link()
    m = sl(1, 1, 1, 1, %{})
    {m, m |> Map.values |> Enum.max()}
    # m = sl(1, 1, 1, 1, %{}, 0)
    # m |> Map.keys()
    # |> Enum.map(fn x -> {Map.fetch!(m, x), x} end)
    # |> Enum.sort_by(fn {a, _b} -> a end)
  end

  defp sl(1, b, c, _index, m) when b > c, do: sl(1, 1, c+1, 1, m)
  defp sl(a, b, c, _index, m) when a > b, do: sl(1, b+1, c, 1, m)
  defp sl(a, b, c, index, m) do
    {_, cubes} = cover_cube_nums(a, b, c, index)
    Logger.info("a: #{a}, b: #{b}, c: #{c}, index: #{index}, cube: #{cubes}")
    cond do
      cubes > @limit ->
	case {a, b, index} do
	  {1, 1, 1} -> m
	  {_, _, 1} -> sl(1, 1, c+1, 1, m)
	  _ -> sl(a+1, b, c, 1, m)
	end
      :else ->
	nm = Map.update(m, cubes, 1, fn x -> x+1 end)
	sl(a, b, c, index+1, nm)
    end

  end



end
