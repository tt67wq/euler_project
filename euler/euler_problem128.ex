defmodule Hexagonal do
  @moduledoc """
  https://projecteuler.net/problem=128
  """

  use GenServer
  require Integer
  require Logger

  @limit 2000

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

  def pos(1), do: {0, 0}
  def pos(n), do: pos(1, n, 1)

  defp pos(index, n, acc) do
    s = 3 * index * index - 3 * index + 2

    cond do
      n < s -> {index - 1, n - acc}
      :else -> pos(index + 1, n, s)
    end
  end

  def get_data_by_lc(0, 0), do: 1
  def get_data_by_lc(l, c), do: 3 * l * l - 3 * l + 2 + c

  def around(1), do: [2, 3, 4, 5, 6, 7]
  def around(n), do: around_lc(n) |> Enum.map(fn {l, c} -> get_data_by_lc(l, c) end)

  defp around_lc(n) do
    {l, c} = pos(n)
    t = 6 * l
    t1 = t - 6

    cond do
      c == 0 ->
        [
          {l + 1, c},
          {l + 1, c + 1},
          {l, c + 1},
          {l - 1, c},
          {l, 6 * l - 1},
          {l + 1, 6 * (l + 1) - 1}
        ]

      c < l ->
        [{l + 1, c}, {l + 1, c + 1}, {l, c + 1}, {l - 1, c}, {l - 1, c - 1}, {l, c - 1}]

      c == l ->
        [{l + 1, c}, {l + 1, c + 1}, {l + 1, c + 2}, {l, c + 1}, {l - 1, c - 1}, {l, c - 1}]

      c > l and c < 2 * l ->
        [{l, c - 1}, {l + 1, c + 1}, {l + 1, c + 2}, {l, c + 1}, {l - 1, c - 1}, {l - 1, c - 2}]

      c == 2 * l ->
        [{l, c - 1}, {l + 1, c + 1}, {l + 1, c + 2}, {l + 1, c + 3}, {l, c + 1}, {l - 1, c - 2}]

      c > 2 * l and c < 3 * l ->
        [{l - 1, c - 3}, {l, c + 1}, {l + 1, c + 2}, {l + 1, c + 3}, {l, c + 1}, {l - 1, c - 2}]

      c == 3 * l ->
        [{l - 1, c - 3}, {l, c - 1}, {l + 1, c + 2}, {l + 1, c + 3}, {l + 1, c + 4}, {l, c + 1}]

      c > 3 * l and c < 4 * l ->
        [{l - 1, c - 3}, {l - 1, c - 4}, {l, c - 1}, {l + 1, c + 3}, {l + 1, c + 4}, {l, c + 1}]

      c == 4 * l ->
        [{l, c + 1}, {l - 1, c - 4}, {l, c - 1}, {l + 1, c + 3}, {l + 1, c + 4}, {l + 1, c + 5}]

      c > 4 * l and c < 5 * l ->
        [{l, c + 1}, {l - 1, c - 4}, {l - 1, c - 5}, {l, c - 1}, {l + 1, c + 4}, {l + 1, c + 5}]

      c == 5 * l ->
        [{l + 1, c + 6}, {l, c + 1}, {l - 1, c - 5}, {l, c - 1}, {l + 1, c + 4}, {l + 1, c + 5}]

      c > 5 * l ->
        [
          # 11
          {l + 1, c + 6},
          {l, rem(c + 1, t)},
          {l - 1, rem(c - 5, t1)},
          {l - 1, c - 6},
          {l, c - 1},
          {l + 1, c + 5}
        ]
    end
  end

  def pd(n) do
    around(n)
    |> Enum.map(fn x -> abs(x - n) end)
    |> Enum.filter(fn x -> cache_prime?(x) end)
    |> Enum.count()
  end

  def solution() do
    start_link()
    sl(1, 0)
  end

  defp sl(index, acc) when acc == @limit, do: index - 1

  defp sl(index, acc) do
    {l, c} = pos(index)

    cond do
      l * 6 - 1 == c or c == 0 ->
        p = pd(index)

        case p do
          3 ->
            Logger.info("get one #{index}, now total #{acc + 1}")
            # Logger.info("#{index}'s pos is #{inspect(pos(index))}")
            sl(index + 1, acc + 1)

          _ ->
            # Logger.debug("#{index}'s pd is #{p}")
            sl(index + 1, acc)
        end

      :else ->
        sl(3 * (l + 1) * (l + 1) - 3 * (l + 1) + 1, acc)
    end
  end
end
