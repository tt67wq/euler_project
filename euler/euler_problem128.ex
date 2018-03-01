defmodule Hexagonal do
  @moduledoc """
  https://projecteuler.net/problem=128
  """

  use GenServer
  require Integer
  require Logger

  @limit 10000000

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

  ### prime judge

  @doc """
  质数检查
  """
  @spec prime?(Integer) :: boolean
  def prime?(1), do: false
  def prime?(2), do: true
  def prime?(3), do: true

  def prime?(x) do
    cond do
      Integer.is_even(x) -> false
      :else -> is_prime(x, 3)
    end
  end

  defp is_prime(x, c) when c * c > x, do: true

  defp is_prime(x, c) do
    cond do
      rem(x, c) == 0 -> false
      :else -> is_prime(x, next_prime(c))
    end
  end

  @doc """
  获得下一个质数
  """
  def next_prime(2), do: 3

  def next_prime(x) do
    cond do
      Integer.is_even(x) -> np(x + 1)
      :else -> np(x + 2)
    end
  end

  defp np(y) do
    cond do
      cache_prime?(y) -> y
      :else -> np(y + 2)
    end
  end

  @doc """
  缓存的质数判断
  """
  def cache_prime?(x) do
    cached_value = get(:prime, x)

    case cached_value do
      nil -> set_and_get(:prime, x, prime?(x))
      _ -> cached_value
    end
  end

  ### real shit

  def pos(1), do: {0, 1}
  def pos(n), do: pos(1, n, 1)

  defp pos(index, n, acc) do
    s = 3 * index * index - 3 * index + 2

    cond do
      n < s -> {index - 1, n - acc + 1}
      :else -> pos(index + 1, n, s)
    end
  end

  def pos_xy(1), do: {0, 0}

  def pos_xy(n) do
    {l, c} = pos(n)
    locate(l, c)
  end

  def locate(l, 1), do: {0, l * 2}
  def locate(l, c), do: locate(l, c, 1, {0, l * 2})

  defp locate(_l, c, index, {x, y}) when index == c, do: {x, y}

  defp locate(l, c, index, {x, y}) do
    cond do
      index <= l -> locate(l, c, index + 1, {x - 1, y - 1})
      index > l and index <= 2 * l -> locate(l, c, index + 1, {x, y - 2})
      index > 2 * l and index <= 3 * l -> locate(l, c, index + 1, {x + 1, y - 1})
      index > 3 * l and index <= 4 * l -> locate(l, c, index + 1, {x + 1, y + 1})
      index > 4 * l and index <= 5 * l -> locate(l, c, index + 1, {x, y + 2})
      :else -> locate(l, c, index + 1, {x - 1, y + 1})
    end
  end

  def xy_map(n), do: 1..n |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, pos_xy(x), x) end)

  def around(n, xym) do
    {x, y} = pos_xy(n)
    [
      Map.fetch!(xym, {x, y + 2}),
      Map.fetch!(xym, {x - 1, y + 1}),
      Map.fetch!(xym, {x - 1, y - 1}),
      Map.fetch!(xym, {x, y - 2}),
      Map.fetch!(xym, {x + 1, y - 1}),
      Map.fetch!(xym, {x + 1, y + 1})
    ]
  end

  def pd(n, xym) do
    around(n, xym)
    |> Enum.map(fn x -> abs(x - n) end)
    |> Enum.filter(fn x -> cache_prime?(x) end)
    |> Enum.count()
  end

  def solution() do
    start_link()
    mp = xy_map(@limit)
    sl(mp, 1, 0)
  end

  defp sl(_, index, acc) when acc == 2000, do: index - 1

  defp sl(mp, index, acc) do
    p = pd(index, mp)

    case p do
      3 ->
        Logger.info("get one, now total #{acc + 1}")
        sl(mp, index + 1, acc + 1)

      _ ->
        sl(mp, index + 1, acc)
    end
  end
end
