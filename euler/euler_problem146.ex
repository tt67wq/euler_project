defmodule Euler146 do
  @moduledoc """
  https://projecteuler.net/problem=146
  """
  @limit 150_000_000

  require Integer
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

  def all_prime([]), do: true

  def all_prime([h | t]) do
    cond do
      cache_prime?(h) -> all_prime(t)
      :else -> false
    end
  end

  def ck_mod(p), do: 0..(p - 1) |> Enum.filter(fn x -> ck(x, p) end)

  defp ck(r, p) do
    res =
      [1, 3, 7, 9, 13, 27]
      |> Enum.map(fn x -> r * r + rem(x, p) end)
      |> Enum.filter(fn x -> rem(x, p) > 0 end)

    length(res) == 6
  end

  def timestamp(), do: :os.system_time(:micro_seconds)

  def solution() do
    t1 = timestamp()
    start_link()

    pMap =
      1..5000
      |> Enum.filter(fn x -> cache_prime?(x) end)
      |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, x, ck_mod(x)) end)

    primes = Map.keys(pMap) |> Enum.sort()

    # res = primes |> Enum.filter(fn x -> Map.fetch!(pMap, x) == [0] end)

    res =
      sl(10, pMap, primes, [])
      |> Enum.filter(fn x -> not cache_prime?(x * x + 19) end)
      |> Enum.filter(fn x -> not cache_prime?(x * x + 21) end)
      |> Enum.sum()

    Logger.info("timeuse: #{timestamp() - t1} ms")
    res
  end

  defp sl(index, _, _, acc) when index > @limit, do: acc

  defp sl(index, pMap, primes, acc) do
    pass =
      primes
      |> Enum.filter(fn x -> x < index * index end)
      |> Enum.map(fn x -> {x, rem(index, x)} end)
      |> check(pMap)

    case pass do
      true ->
        cond do
          [
            index * index + 1,
            index * index + 3,
            index * index + 7,
            index * index + 9,
            index * index + 13,
            index * index + 27
          ]
          |> all_prime() ->
            Logger.info("#{index}: #{pass}")
            sl(index + 10, pMap, primes, [index | acc])

          :else ->
            sl(index + 10, pMap, primes, acc)
        end

      false ->
        sl(index + 10, pMap, primes, acc)
    end
  end

  defp check([], _), do: true

  defp check([{p, r} | t], pMap) do
    vals = Map.fetch!(pMap, p)

    cond do
      Enum.member?(vals, r) -> check(t, pMap)
      :else -> false
    end
  end
end
