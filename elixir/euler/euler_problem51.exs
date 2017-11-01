defmodule PrimeDigitReplacements do
  @moduledoc """
  https://projecteuler.net/problem=51
  最小的数字，可替换位必然为1，2，3中的一个
  """
  require Logger
  require Integer
  use GenServer

  # -------------------------- 质数工具函数 --------------------------
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

  # -------------------------- 质数工具函数 --------------------------

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
  最后的数字必然是不能替换的位置，不然2替换上去必然不为质数
  ## Example

      iex> generate_5digits_pattern
      [[0, 0, 0, "x", "y"], [0, 0, "x", 0, "y"], [0, "x", 0, 0, "y"],
      ["x", 0, 0, 0, "y"]]
  """
  def generate_5digits_pattern(), do: ["x", "p", "p", "p"] |> arrange() |> Enum.map(fn x -> x ++ ["y"] end)
  def generate_6digits_pattern(), do: ["x","y", "p", "p", "p"] |> arrange() |> Enum.map(fn x -> x ++ ["z"] end)


  @doc """
  列表中元素替换
  ## Example

      iex> elem_replace([1,2,1,3,4], 1, 5)
      [5, 2, 5, 3, 4]

  """
  def elem_replace(lst, a, b), do: er(lst, lst, 0, a, b)
  defp er(lst, [], _index, _a, _b), do: lst
  defp er(lst, [h|t], index, a, b) do
    cond do
      a == h ->
	nlst = List.replace_at(lst, index, b)
	er(nlst, t, index + 1, a, b)
      :else -> er(lst, t, index + 1, a, b)
    end
  end

  @doc """
  ## Example

      iex> list2int([12,23,123])
      1223123
  """
  def list2int(lst), do: l2i(lst, 0)
  defp l2i([], acc), do: acc
  defp l2i([h|t], acc), do: l2i(t, acc * 10 + h)

  @doc """
  测试这个模板能渲染出多少个质数
  ## Example

      iex> pattern_rend([5, 6, "p", "p", 3])
      [56003, 56113, 56333, 56443, 56663, 56773, 56993]

  """
  def pattern_rend(pattern) do
    0..9 |> Enum.map(fn x -> elem_replace(pattern, "p", x) end)
    |> Enum.map(fn x -> list2int(x) end)
    |> Enum.filter(fn x -> cache_prime?(x) end)
  end

  @doc """
  生成5位模板
  """
  def pattern5_render(pattern) do
    for a <- 0..9,
      b <- [1, 3, 5, 7, 9] do
	pattern |> elem_replace("x", a) |> elem_replace("y", b)
    end
  end

  @doc """
  生成6位模板
  """
  def pattern6_render(pattern) do
    for a <- 0..9,
      b <- 0..9,
      c <- [1, 3, 5, 7, 9] do
	pattern |> elem_replace("x", a) |> elem_replace("y", b) |> elem_replace("z", c)
    end
  end

  def solution() do
    start_link()
    # patterns_list = generate_5digits_pattern() |> Enum.map(fn x -> pattern5_render(x) end)
    # patterns_list |> Enum.map(fn x -> sl(x) end)
    patterns_list = generate_6digits_pattern() |> Enum.map(fn x -> pattern6_render(x) end)
    patterns_list |> Enum.map(fn x -> sl(x) end)
  end

  defp sl(patterns) do
    patterns
    |> Enum.map(fn x -> pattern_rend(x) end)
    |> Enum.filter(fn x -> length(x) == 8 end)
  end
end
