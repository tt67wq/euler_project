defmodule ModifiedFibonacciGoldenNuggets do
  @moduledoc """
  https://projecteuler.net/problem=140
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

      :error ->
        {:reply, nil, state}
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

  def fab(0), do: 1
  def fab(1), do: 4
  def fab(n), do: cache_fab(n - 1) + cache_fab(n - 2)

  def cache_fab(n) do
    v = get(:fab, n)

    case v do
      nil -> set_and_get(:fab, n, fab(n))
      _ -> v
    end
  end

  # ==============================================

  def sqrt?(n), do: sqrt(n, 1)
  defp sqrt(0, _), do: true
  defp sqrt(n, _) when n < 0, do: false
  defp sqrt(n, index), do: sqrt(n - index, index + 2)

  def ag(x), do: 5 * x * x + 14 * x + 1

  def solution() do
    start_link()
    sqs = 1..10000 |> Enum.map(fn x -> x * x end)

    1..10000
    |> Stream.map(fn x -> {x, ag(x)} end)
    |> Stream.filter(fn {_, x} -> Enum.member?(sqs, x) end)
    |> Stream.map(fn {_, x} -> :math.sqrt(x) |> round() end)
    |> Enum.to_list()

    # 1..10
    # |> Stream.map(fn x -> cache_fab(2 * x) * cache_fab(2 * x + 1) end)
    # |> Enum.to_list()
  end
end
