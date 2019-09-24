defmodule ProductSumNumbers do
  @moduledoc """
  https://projecteuler.net/problem=88
  """
  require Logger
  @limit 12000

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


  def get_k(list) do
    p = list |> Enum.reduce(1, fn x, acc -> x * acc end)
    p - Enum.sum(list) + length(list)
  end

  def product(list), do: list |> Enum.reduce(1, fn x, acc -> x * acc end)

  def generate_next([h]), do: [h+1]
  def generate_next([h1, h2|t]) when h1 >= h2, do: [2|generate_next([h2|t])]
  def generate_next([h1, h2|t]), do: [h1+1, h2|t]

  # def max?(list) do
  #   [_h|t] = list |> Enum.reverse
  #   t == List.duplicate(2, length(list) - 1)
  # end

  def all2?([]), do: true
  def all2?([h|t]) do
    case h do
      2 -> all2?(t)
      _ -> false
    end
  end

  def generate_next_stage([h|t]) do
    case h do
      2 -> [2|generate_next_stage(t)]
      _ -> [2|generate_next(t)]
    end
  end

  
  def product_sum(n), do: psn(List.duplicate(2, n), List.duplicate(2, n) |> get_k(), [])
  defp psn(list, k, acc) when k > @limit do
    [_|t] = list |> Enum.reverse
    cond do
      all2?(t) -> acc
      :else ->
	nlist = list |> generate_next_stage
	psn(nlist, nlist |> get_k(), acc)
    end
  end

  defp psn(list, k, acc) do
    nlist = list |> generate_next
    psn(nlist, nlist |> get_k(), [{k, list, list |> product()}|acc])
  end

  def uniq(list), do: list |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end) |> MapSet.to_list()

  def set_if_less(k, s) do
    v = get(:ps, k)
    case v do
      nil -> set(:ps, k, s)
      _ ->
	cond do
	  s < v -> set(:ps, k, s)
	  :else -> nil
	end
    end
  end


  def solution() do
    start_link()
    product_sum(2) |> Enum.map(fn {k, _, s} -> set_if_less(k, s) end)
    product_sum(3) |> Enum.map(fn {k, _, s} -> set_if_less(k, s) end)
    product_sum(4) |> Enum.map(fn {k, _, s} -> set_if_less(k, s) end)
    product_sum(5) |> Enum.map(fn {k, _, s} -> set_if_less(k, s) end)
    product_sum(6) |> Enum.map(fn {k, _, s} -> set_if_less(k, s) end)
    product_sum(7) |> Enum.map(fn {k, _, s} -> set_if_less(k, s) end)
    product_sum(8) |> Enum.map(fn {k, _, s} -> set_if_less(k, s) end)
    product_sum(9) |> Enum.map(fn {k, _, s} -> set_if_less(k, s) end)
    product_sum(10) |> Enum.map(fn {k, _, s} -> set_if_less(k, s) end)
    product_sum(11) |> Enum.map(fn {k, _, s} -> set_if_less(k, s) end)
    product_sum(12) |> Enum.map(fn {k, _, s} -> set_if_less(k, s) end)
    product_sum(13) |> Enum.map(fn {k, _, s} -> set_if_less(k, s) end)

    2..@limit |> Enum.map(fn x -> get(:ps, x) end)
    |> uniq() |> Enum.sum()
    
  end


  
end
