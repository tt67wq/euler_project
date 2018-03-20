defmodule LargeRepunitFactors do
  @moduledoc """
  https://projecteuler.net/problem=132
  https://en.wikipedia.org/wiki/Repunit
  """

  use GenServer
  require Integer
  require Logger

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

  @doc """
  质因数分解
  """
  @spec factorization(integer) :: map
  def factorization(n), do: fac(n, 2, [])
  defp fac(n, index, acc) when index * index > n and n > 1, do: [n | acc]

  defp fac(n, index, acc) do
    case rem(n, index) == 0 do
      true -> fac(div(n, index), index, [index | acc])
      _ -> fac(n, next_prime(index), acc)
    end
  end

  def cache_factorization(n) do
    v = get(:fac, n)
    case v do
      nil -> set_and_get(:fac, n, factorization(n))
      _ -> v
    end
  end

  # 暂时实验
  def r(n), do: r(n, 1, 1)
  defp r(n, index, acc) when index == n, do: acc
  defp r(n, index, acc), do: r(n, index + 1, acc * 10 + 1)

  def pow(m, n), do: :math.pow(m, n) |> round()

  def combine_of_2_and_5() do
    for x <- 0..10,
        y <- 0..10 do
      pow(2, x) * pow(5, y)
    end
    |> Enum.sort()
  end

  def fac_r(n), do: r(n) |> factorization()

  def all_facs(n), do: 2..div(n + 1, 2) |> Enum.filter(fn x -> rem(n, x) == 0 end)

  defp get_new_facs(m, n), do: div(r(m), r(n)) |> cache_factorization()

  def get_new_facs(n) do
    fs = all_facs(n) |> Enum.reverse()

    case length(fs) do
      0 ->
        get_new_facs(n, 1)

      1 ->
        [h] = fs
        get_new_facs(n, div(n, h))

      _ ->
        [h1, h2 | _t] = fs

        get_new_facs(n, h1)
        |> Enum.filter(fn x -> Enum.member?(get_new_facs(n, h2), x) end)
    end
  end

  def solution() do
    start_link()
    nums = combine_of_2_and_5()
    sl(nums, [])
  end

  defp sl([1 | t], acc), do: sl(t, acc)
  defp sl([2 | t], acc), do: sl(t, [11 | acc])
  defp sl([5 | t], acc), do: sl(t, [41, 271 | acc])

  defp sl(_, acc) when length(acc) > 40, do: acc

  defp sl([h | t], acc) do
    Logger.info(h)
    new_facs = get_new_facs(h)
    Logger.info("#{inspect(new_facs)}")
    sl(t, acc ++ new_facs)
  end
end
