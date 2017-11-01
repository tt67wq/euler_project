defmodule AmicableNumbers do
  @moduledoc """
  Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
  If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.
  For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
  Evaluate the sum of all the amicable numbers under 10000.
  """
  use GenServer
  require Logger

  ### GenServer API
  def init(state), do: {:ok, state}

  def handle_call({:get, n}, _from, state) do
    case Map.fetch(state, n) do
      {:ok, value} -> {:reply, value, state}
      :error -> {:reply, nil, state}
    end
  end

  def handle_cast({:set, n, value}, state) do
    {:noreply, Map.update(state, n, value, &(&1))}
  end

  ### Client
  def start_link(state \\ %{}) do
    GenServer.start_link(__MODULE__, state, name: __MODULE__)
  end

  def get(n), do: GenServer.call(__MODULE__, {:get, n})
  def set(n, value), do: GenServer.cast(__MODULE__, {:set, n, value})
  
  @spec sum_divisors(integer) :: integer
  def sum_divisors(1), do: 1
  def sum_divisors(n) do
    case get(n) do
      nil ->
	value = 1..n-1 |> Enum.filter(fn x -> rem(n, x) == 0 end) |> Enum.sum()
	set(n, value)
	value
      value -> value
    end
  end

  @spec amicable?(integer) :: boolean
  def amicable?(n), do: n |> sum_divisors != n and n |> sum_divisors |> sum_divisors == n


  @spec amicable_numbers(integer) :: list
  def amicable_numbers(n), do: 1..n |> Enum.filter(fn x -> amicable?(x) end)
  
  @spec sum_amicable_numbers(integer) :: integer
  def sum_amicable_numbers(n), do: 1..n |> Enum.filter(fn x -> amicable?(x) end) |> Enum.sum()
  
end
