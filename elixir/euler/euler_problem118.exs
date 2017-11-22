defmodule PandigitalPrimeSets do
  @moduledoc """
  https://projecteuler.net/problem=118
  """

  require Integer
  use GenServer
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
      nil ->
	value = prime?(x)
	set(:prime, x, value)
	value
      _ -> cached_value
    end
  end

  @doc """
  ## Example
  
      iex> Generator.arrange([1, 2, 3])
      [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
  """
  @spec arrange(List) :: List
  def arrange(lst), do: arg(lst) |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end) |> MapSet.to_list()
  defp arg(lst) when length(lst) == 1, do: [lst]
  defp arg([h|t]), do: arrange(t) |> Enum.reduce([], fn x, acc -> insert(h, x) ++ acc end)
  defp insert(n, lst), do: 0..length(lst) |> Enum.map(fn x -> List.insert_at(lst, x, n) end)

  @doc """
  ## Example

      iex> Generator.choose([1,2,3], 2)
      [[1, 2], [1, 3], [2, 3]]
  """
  @spec choose(List, Integer) :: List
  def choose(lst, n), do: chs(lst, n) |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end) |> MapSet.to_list()
  defp chs(lst, n) when length(lst) == n, do: [lst]
  defp chs(lst, 1), do: lst |> Enum.map(fn x -> [x] end)
  defp chs([h|t], n), do: (choose(t, n-1) |> Enum.map(fn x -> [h|x] end)) ++ choose(t, n)

  @doc """
  ## Example

      iex> list2int([12,23,123])
      1223123
  """
  def list2int(lst), do: l2i(lst, 0)
  defp l2i([], acc), do: acc
  defp l2i([h|t], acc), do: l2i(t, acc * 10 + h)

  def all_prime?(list), do: ap(list)
  defp ap([]), do: true
  defp ap([h|t]) do
    cond do
      cache_prime?(h) -> ap(t)
      :else -> false
    end
  end

  def cache_choose(num) do
    v = get(:ch, num)
    case v do
      nil -> set_and_get(:ch, num, choose(1..8|>Enum.to_list, num))
      _ -> v
    end
  end

  
  def sub_prime(list), do: asp(list, 1, [])
  defp asp(_list, count, acc) when count == 6, do: acc
  defp asp(list, count, acc) do
    ps = cache_choose(count)
    |> Enum.map(fn x -> split_by_index(list, x) |> Enum.map(fn x -> x|>list2int end) end)
    |> Enum.filter(fn x -> all_prime?(x) end)
    |> Enum.map(fn x -> Enum.sort(x) end)
    cond do
      length(ps) > 0 -> asp(list, count+1, acc ++ ps)
      :else -> asp(list, count+1, acc)
    end
  end

  def split_by_index(list, indexes), do: sbi(list, indexes, 0, [], [])
  defp sbi(list, [], _, _, acc), do: [list|acc] |> Enum.reverse
  defp sbi(list, [h|t], index, bcc, acc) when index == h, do: sbi(list, t, index, [], [bcc|>Enum.reverse|acc])
  defp sbi([h|t], indexes, index, bcc, acc), do: sbi(t, indexes, index+1, [h|bcc], acc)

  def int2list(num), do: i2l(num, [])
  defp i2l(0, acc), do: acc
  defp i2l(num, acc), do: i2l(num |> div(10), [num |> rem(10)|acc])

  def ps2list(ps), do: ps |> Enum.reverse |> Enum.reduce([], fn x, acc -> int2list(x) ++ acc end)

  def solution() do
    start_link()
    list = 1..9 |> Enum.to_list |> arrange
    |> Enum.filter(fn x -> not Enum.member?([4,6,8], List.last(x)) end)
    r = sl(list, MapSet.new())
    MapSet.size(r)
  end

  defp sl([], acc), do: acc
  defp sl([h|t], acc) do
    ps = sub_prime(h)
    cond do
      length(ps) > 0 ->
	Logger.info("acc: #{MapSet.size(acc)}")
	Logger.info("#{inspect ps}")
	sl(t,  ps |> Enum.reduce(acc, fn x, bcc -> MapSet.put(bcc, x) end))
      :else -> sl(t,  acc)
    end
  end

end
