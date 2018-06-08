defmodule Euler149 do
  @moduledoc """
  https://projecteuler.net/problem=149
  """
  require Integer
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

  # 同余定理
  def pow_mod(m, 1, k), do: Integer.mod(m, k)
  def pow_mod(m, 2, k), do: Integer.mod(m * m, k)

  def pow_mod(m, n, k) do
    t = Integer.mod(m, k)

    cond do
      t == 0 ->
        0

      :else ->
        cond do
          Integer.is_even(n) ->
            pow_mod(m, 2, k) |> pow_mod(div(n, 2), k)

          :else ->
            ((pow_mod(m, 2, k) |> pow_mod(div(n - 1, 2), k)) * t) |> Integer.mod(k)
        end
    end
  end

  def cache_lfg(k) do
    v = get(:lag, k)

    case v do
      nil -> set_and_get(:lag, k, lagged_fibonacci_generator(k))
      _ -> v
    end
  end

  def lagged_fibonacci_generator(k) when k <= 55 do
    r1 = (200_003 * rem(k, 1_000_000)) |> rem(1_000_000)
    r2 = (300_007 * pow_mod(k, 3, 1_000_000)) |> rem(1_000_000)
    rem(100_003 - r1 + r2, 1_000_000) - 500_000
  end

  def lagged_fibonacci_generator(k) when k <= 4_000_000 do
    r1 = cache_lfg(k - 24)
    r2 = cache_lfg(k - 55)
    rem(r1 + r2 + 1_000_000, 1_000_000) - 500_000
  end
end
