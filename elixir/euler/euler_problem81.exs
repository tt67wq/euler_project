defmodule PathSum do
  @moduledoc """
  https://projecteuler.net/problem=81
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

  # ----------------- cache -----------------

  def min_path(nil), do: nil
  def min_path(matrix) do
    # Logger.info("matrix: #{inspect matrix}")
    up = get_up(matrix)
    left = get_left(matrix)
    # Logger.info("left: #{inspect left}, up: #{inspect up}")

    lpath = if up == nil do
      left |> List.first()
    else
      cache_min_path(left)
    end

    upath = if left == nil do
      up |> Enum.map(fn [x] -> x end)
    else
      cache_min_path(up)
    end

    # Logger.info("upath: #{inspect upath}, lpath: #{inspect lpath}")

    case {upath, lpath} do
      {nil, nil} -> [matrix |> List.first() |> List.first()]
      {nil, _} -> append(lpath, List.last(matrix) |> List.last())
      {_, nil} -> append(upath, List.last(matrix) |> List.last())
      _ ->
	cond do
	  Enum.sum(upath) > Enum.sum(lpath) -> append(lpath, List.last(matrix) |> List.last())
	  :else -> append(upath, List.last(matrix) |> List.last())
	end
    end
  end

  def cache_min_path(matrix) do
    v = get(:matrix, matrix)
    case v do
      nil -> set_and_get(:matrix, matrix, min_path(matrix))
      _ -> v
    end
  end


  def get_up(matrix) do
    case length(matrix) do
      1 -> nil
      _ -> matrix |> pop_last()
    end
  end

  def get_left(matrix) do
    case length(List.first(matrix)) do
      1 -> nil
      _ -> matrix |> Enum.map(fn x -> x |> pop_last() end)
    end
  end

  def pop(list) do
    [_|t] = list
    t
  end

  def pop_last(list), do: list |> Enum.reverse() |> pop() |> Enum.reverse()

  def append(list, elem) do
    rl = list |> Enum.reverse()
    [elem|rl] |> Enum.reverse()
  end


  def to_int_list(list), do: list |> Enum.map(fn x -> String.to_integer(x) end)

  def solution() do
    start_link()
    {:ok, content} = File.read("p081_matrix.txt")
    content |> String.split("\n")
    |> Enum.filter(fn x -> x != "" end)
    |> Enum.map(fn x -> String.split(x, ",") end)
    |> Enum.map(fn x -> to_int_list(x) end)
    |> cache_min_path()
  end

end
