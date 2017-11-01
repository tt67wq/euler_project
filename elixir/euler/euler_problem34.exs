defmodule DigitFactorials do
  @moduledoc """
  145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
  Find the sum of all numbers which are equal to the sum of the factorial of their digits.
  Note: as 1! = 1 and 2! = 2 are not sums they are not included.
  """
  use GenServer

  @doc """
  GenServer.init/1 callback
  """
  def init(state), do: {:ok, state}

  @doc """
  GenServer.handle_call/3 callback
  """
  def handle_call({:factorial, n}, _from, state) do
    case Map.fetch(state, n) do
      {:ok, value} -> {:reply, value, state}
      :error -> {:reply, nil, state}
    end
  end

  def handle_cast({:cache, n, value}, state) do
    {:noreply, Map.update(state, n, value, &(&1))}
  end
  ### Client API / Helper functions

  def start_link(state \\ %{}) do
    GenServer.start_link(__MODULE__, state, name: __MODULE__)
  end

  def factorial(n), do: GenServer.call(__MODULE__, {:factorial, n})
  def cache(n, value), do: GenServer.cast(__MODULE__, {:cache, n, value})

  
  def is_curious?(1), do: false
  def is_curious?(2), do: false
  def is_curious?(number), do: curious(number, number, 0)
  defp curious(number, 0, acc), do: acc == number
  defp curious(number, _index, acc) when acc > number, do: false
  defp curious(number, index, acc), do: curious(number, div(index, 10), acc + get_factorial(rem(index, 10)))
  def get_factorial(0), do: 1
  def get_factorial(number) do
    case factorial(number) do
      nil ->
	value = get_factorial(number-1) * number
	cache(number, value)
	value
      value -> value
    end
  end

  def util(n), do: util(n, 1, [])
  defp util(n, index, acc) when index > n, do: acc
  defp util(n, index, acc) do
    cond do
      is_curious?(index) -> util(n, index+1, [index|acc])
      true -> util(n, index+1, acc)
    end
  end
end
