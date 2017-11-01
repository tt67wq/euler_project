defmodule LongestCollatzSequence do
  @moduledoc """
  The following iterative sequence is defined for the set of positive integers:

  n → n/2 (n is even)
  n → 3n + 1 (n is odd)

  Using the rule above and starting with 13, we generate the following sequence:

  13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
  It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

  Which starting number, under one million, produces the longest chain?

  NOTE: Once the chain starts the terms are allowed to go above one million.
  """
  use GenServer
  require Logger
  require Integer

  ## GenServer API
  def init(state), do: {:ok, state}

  def handle_call({:get, n}, _from, state) do
    case Map.fetch(state, n) do
      {:ok, l} -> {:reply, l, state}
      :error -> {:reply, nil, state}
    end
  end

  def handle_cast({:set, n, l}, state) do
    {:noreply, Map.update(state, n, l, &(&1))}
  end

  ### Client API

  def start_link(state \\ %{1 => 4}) do
    GenServer.start_link(__MODULE__, state, name: __MODULE__)
  end

  def get(n), do: GenServer.call(__MODULE__, {:get, n})
  def set(n, l), do: GenServer.cast(__MODULE__, {:set, n, l})

  ## body
  def calculate_chain(1), do: 4
  def calculate_chain(2), do: 2
  def calculate_chain(n), do: calculate_chain(n, n, 1)
  defp calculate_chain(n, 1, l) do
    set(n, l)
    l
  end

  defp calculate_chain(n, index, l) when Integer.is_even(index) do
    tl = get(index)
    case tl do
      nil ->
	calculate_chain(n, div(index, 2), l+1)
      _ ->
	set(n, tl + l)
	tl + l
    end
  end
  defp calculate_chain(n, index, l) do
    tl = get(index)
    case tl do
      nil ->
	calculate_chain(n, 3 * index + 1, l+1)
      _ ->
	set(n, tl + l)
	tl + l
    end
  end

  def calculate_util(n), do: calculate_util(n, 1, {1, 4})
  defp calculate_util(n, n, acc), do: acc
  defp calculate_util(n, index, {_k, value}=acc) do
    l = calculate_chain(index)
    case value > l do
      true -> calculate_util(n, index+1, acc)
      false -> calculate_util(n, index+1, {index, l})
    end
  end
end
