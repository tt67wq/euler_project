defmodule EulerProblem130 do
  @moduledoc """
  https://projecteuler.net/problem=130
  """
  @limit 25
  require Integer
  use GenServer

  # 多路缓存
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

  ### Client
  def start_link(state \\ %{}) do
    GenServer.start_link(__MODULE__, state, name: __MODULE__)
  end

  def get(tag, key), do: GenServer.call(__MODULE__, {:get, tag, key})
  def set(tag, key, value), do: GenServer.cast(__MODULE__, {:set, tag, key, value})

  def set_and_get(tag, key, value) do
    set(tag, key, value)
    value
  end

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

  def a(n) do
    case Integer.gcd(n, 10) do
      1 -> a(n, 1, 1)
      _ -> 0
    end
  end

  defp a(_n, 0, acc), do: acc
  defp a(n, x, acc), do: a(n, rem(10 * x + 1, n), acc + 1)

  def solution() do
    start_link()
    sl(3, [], 0)
  end

  defp sl(_, acc, count) when count == @limit, do: acc

  defp sl(index, acc, count) do
    cond do
      cache_prime?(index) ->
        sl(index + 2, acc, count)

      :else ->
        an = a(index)

        case an do
          0 ->
            sl(index + 2, acc, count)

          _ ->
            case rem(index - 1, an) do
              0 -> sl(index + 2, [index | acc], count + 1)
              _ -> sl(index + 2, acc, count)
            end
        end
    end
  end
end
