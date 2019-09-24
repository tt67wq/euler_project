defmodule PrimePairConnection do
  @moduledoc """
  https://projecteuler.net/problem=134
  实际上这是用扩展欧几里得算法来写的
  """
  @limit 30
  use GenServer
  require Integer
  require Logger
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
  获得小于n的所有素数
  """
  def get_primes_before(n) do
    data = 2..n |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, x, true) end)
    root = :math.sqrt(n) |> round()

    2..root
    |> Enum.filter(fn x -> cache_prime?(x) end)
    |> Enum.reduce(data, fn x, acc -> filtrate(2 * x, x, n, acc) end)
    |> Map.to_list()
    |> Enum.filter(fn {_, x} -> x end)
    |> Enum.map(fn {x, _} -> x end)
  end

  defp filtrate(index, _p, n, data) when index > n, do: data
  defp filtrate(index, p, n, data), do: filtrate(index + p, p, n, Map.put(data, index, false))

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

  def num_length(num), do: nl(num, 1)
  defp nl(0, acc), do: acc
  defp nl(num, acc), do: nl(div(num, 10), acc * 10)

  def extend_gcd(a, b), do: eg(a, b, {0, 1}, {1, 0})

  defp eg(a, 0, {_, lx}, {_, ly}), do: {lx, ly, a}

  defp eg(a, b, {x, lx}, {y, ly}) do
    quotient = div(a, b)
    eg(b, rem(a, b), {lx - quotient * x, x}, {ly - quotient * y, y})
  end

  def solution() do
    start_link()
    ps = get_primes_before(@limit + 100)
    sl(ps |> Enum.sort(), []) |> Enum.sum()
  end

  defp sl([2, 3 | t], acc), do: sl(t, acc)

  defp sl([h | _], acc) when h > @limit, do: acc

  defp sl([h1, h2 | t], acc) do
    d = h2 - h1
    a = num_length(h1)
    {x, _, _} = extend_gcd(a, h2)
    y = rem(x * d, h2)

    # Logger.info("#{x}, #{y}")
    s =
      cond do
        y < 0 ->
          (y + h2) * a + h1

        :else ->
          y * a + h1
      end

    Logger.info("#{s}")
    sl([h2 | t], [s | acc])
  end
end
