defmodule SquareRootConvergents do
  @moduledoc """
  It is possible to show that the square root of two can be expressed as an infinite continued fraction.

  √ 2 = 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) = 1.414213...

  By expanding this for the first four iterations, we get:

  1 + 1/2 = 3/2 = 1.5
  1 + 1/(2 + 1/2) = 7/5 = 1.4
  1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
  1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...

  The next three expansions are 99/70, 239/169, and 577/408, but the eighth expansion, 1393/985, 
  is the first example where the number of digits in the numerator exceeds the number of digits in the denominator.

  In the first one-thousand expansions, how many fractions contain a numerator with more digits than denominator?
  """
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
  计算第N次迭代的分子和分母
  """
  @spec iteration(Integer) :: Tuple
  def iteration(1), do: {3, 2}
  def iteration(n) do
    {numerator, denominator} = cache_iteration(n - 1)
    {numerator + 2 * denominator, numerator + denominator}
  end

  def cache_iteration(n) do
    value = get(:iter, n)
    case value do
      nil ->
	value = iteration(n)
	set(:iter, n, value)
	value
      _ -> value
    end
  end

  def digit_more?({a, b}), do: length(Integer.to_charlist(a)) > length(Integer.to_charlist(b))

  def solution(), do: 1..1000 |> Enum.filter(fn x -> iteration(x) |> digit_more?() end) |> length()
end
