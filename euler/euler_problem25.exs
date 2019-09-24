defmodule Euler do
  @moduledoc """
  The Fibonacci sequence is defined by the recurrence relation:

  Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
  Hence the first 12 terms will be:

  F1 = 1
  F2 = 1
  F3 = 2
  F4 = 3
  F5 = 5
  F6 = 8
  F7 = 13
  F8 = 21
  F9 = 34
  F10 = 55
  F11 = 89
  F12 = 144
  The 12th term, F12, is the first term to contain three digits.

  What is the index of the first term in the Fibonacci sequence to contain 1000 digits?
  """
  use GenServer

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

  def start_link(state \\ %{}) do
    GenServer.start_link(__MODULE__, state, name: __MODULE__)
  end

  def get(n), do: GenServer.call(__MODULE__, {:get, n})
  def set(n, value), do: GenServer.cast(__MODULE__, {:set, n, value})


  def fib(1), do: 1
  def fib(2), do: 1
  def fib(n) do
    case get(n) do
      nil ->
	v = fib(n-1) + fib(n-2)
	set(n, v)
	v
      value -> value
    end
  end

  def first_n_digit(n), do: first(n, 0, 1)
  defp first(n, index, acc)  do
    case length(Integer.to_charlist(acc)) > n do
      true -> index
      _ -> first(n, index+1, fib(index+1))
    end
  end
end
