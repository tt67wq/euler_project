defmodule SpecialIsoscelesTriangles do
  @moduledoc """
  https://projecteuler.net/problem=138
  """
  @limit 1_000_000
  require Integer

  def get_triangle_set(), do: gts(2, 1, [])

  defp gts(m, n, acc) when 2 * (n * n + m * m) > @limit, do: acc
  defp gts(m, n, acc) when n >= m, do: gts(m + 1, 1, acc)

  defp gts(m, n, acc) do
    cond do
      rem(m + n, 2) == 0 ->
        gts(m, n + 1, acc)

      :else ->
        cond do
          Integer.gcd(m, n) != 1 ->
            gts(m, n + 1, acc)

          :else ->
            a = m * m - n * n
            b = 2 * m * n
            c = m * m + n * n

            cond do
              a > b ->
                gts(m, n + 1, [{b, a, c} | acc])

              :else ->
                gts(m, n + 1, acc)
            end
        end
    end
  end

  def try_sentence() do
    get_triangle_set()
    |> Enum.sort_by(fn {x, _, _} -> x end)
    |> Enum.filter(fn {a, b, _} -> abs(b - 2 * a) == 1 end)
    |> Enum.map(fn {_, _, c} -> c end)
  end

  # ================================================
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
  def fab(1), do: 1
  def fab(n), do: cache_fab(n - 1) + cache_fab(n - 2)

  def cache_fab(n) do
    v = get(:fab, n)

    case v do
      nil -> set_and_get(:fab, n, fab(n))
      _ -> v
    end
  end

  def solution() do
    start_link()

    1..12
    |> Enum.map(fn x -> cache_fab(6 * x + 2) |> div(2) end)
    # |> Enum.sum()
  end
end
