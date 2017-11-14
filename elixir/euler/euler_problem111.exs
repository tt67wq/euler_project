defmodule PrimesWithRuns do
  @moduledoc """
  https://projecteuler.net/problem=111
  """

  @base ["x", "x", "x", "x", "x", "x", "x", "x", "x", "x"]
  # @base ["x", "x", "x", "x"]
  require Logger
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


  @doc """
  质数检查
  """
  @spec prime?(Integer) :: boolean
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
  找到第N个质数
  """
  @spec n_prime(Integer) :: Integer
  def n_prime(1), do: 2
  def n_prime(n), do: np(n, 1, 2)
  defp np(n, index, acc) when index == n, do: acc
  defp np(n, index, acc) when index < n, do: np(n, index+1, next_prime(acc))

  def cache_n_prime(n) do
    cached_value = get(:n_prime, n)
    case cached_value do
      nil ->
	value = n_prime(n)
	set(:n_prime, n, value)
	value
      _ -> cached_value
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

      iex> Generator.choose([1,2,3], 2)
      [[1, 2], [1, 3], [2, 3]]
  """
  @spec choose(List, Integer) :: List
  def choose(lst, n), do: chs(lst, n) |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end) |> MapSet.to_list()
  defp chs(lst, n) when length(lst) == n, do: [lst]
  defp chs(lst, 1), do: lst |> Enum.map(fn x -> [x] end)
  defp chs([h|t], n), do: (choose(t, n-1) |> Enum.map(fn x -> [h|x] end)) ++ choose(t, n)

  def templates(l, n), do: 1..l |> Enum.to_list |> choose(n) # |> Enum.map(fn x -> x |> Enum.reduce(["x", "x", "x", "x", "x", "x", "x", "x", "x", "x"], fn x, acc -> acc |> List.replace_at(x-1, "y") end) end)

  def render(template), do: render(template, [[]])
  defp render([], acc) do
    acc |> Enum.map(fn x -> x |> Enum.reverse end)
    |> Enum.filter(fn x -> (x |> List.first())!=0 end)
    |> Enum.filter(fn x -> not Enum.member?([0, 2, 4, 6, 8], (x |> List.last())) end)
    |> Enum.map(fn x -> x |> list2int end)
  end
  defp render(["x"|t], acc), do: render(t, 0..9 |> Enum.reduce([], fn y, bcc -> bcc ++ (acc |> Enum.map(fn x -> [y|x] end)) end))
  defp render([h|t], acc), do: render(t, acc |> Enum.map(fn x -> [h|x] end))

  @doc """
  ## Example

      iex> list2int([12,23,123])
      1223123
  """
  def list2int(lst), do: l2i(lst, 0)
  defp l2i([], acc), do: acc
  defp l2i([h|t], acc), do: l2i(t, acc * 10 + h)

  def count_prime(list), do: list |> Enum.filter(fn x -> x |> cache_prime? end) |> Enum.sum()
  
  defp m(l, d, c) do
    # Logger.info("#{l}, #{d}, #{c}")
    templates(l, c)
    |> Enum.map(fn x -> x |> Enum.reduce(@base, fn x, acc -> acc |> List.replace_at(x-1, d) end) end)
    |> Enum.filter(fn x -> not Enum.member?([0, 2, 4, 6, 8], (x |> List.last())) end)
    |> Enum.map(fn x -> x |> render() end)
    |> Enum.map(fn x -> x |> count_prime end)
    |> Enum.sum
  end

  def m(d), do: calculate(d, 10)
  defp calculate(d, c) do
    s = m(10, d, c)
    Logger.info("d: #{d}, c: #{c}, s: #{s}")
    cond do
      s == 0 -> calculate(d, c-1)
      :else -> s
    end
  end

  def solution() do
    start_link()
    0..9 |> Enum.reduce(0, fn x, acc -> acc + m(x) end)
  end

  
end
