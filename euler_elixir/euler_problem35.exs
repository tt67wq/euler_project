defmodule CircularPrimes do
  @moduledoc """
  The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.
  There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
  How many circular primes are there below one million?
  """
  use GenServer
  require Logger

  @doc """
  GenServer.init/1 callback
  """
  def init(state), do: {:ok, state}

  @doc """
  GenServer.handle_call/3 callback
  """
  def handle_call({:in?, x}, _from, state) do
    cond do
      Enum.member?(state, x) -> {:reply, true, state}
      true -> {:reply, false, state}
    end
  end

  def handle_cast({:add, x}, state) do
    {:noreply, [x | state]}
  end

  ### Client API / Helper functions

  def start_link(state \\ []) do
    GenServer.start_link(__MODULE__, state, name: __MODULE__)
  end

  def in?(x), do: GenServer.call(__MODULE__, {:in?, x})
  def add(x), do: GenServer.cast(__MODULE__, {:add, x})

  def rotate(x, 0), do: x
  def rotate(x, number), do: rotate_list(String.to_charlist(x), number)
  defp rotate_list(lst, 0), do: List.to_string(lst)
  defp rotate_list([h|t], number), do: rotate_list(t ++ [h], number - 1)

  def isPrime(x) do
    cond do
      in?(x) -> true
      2..x |> Enum.filter(fn a -> rem(x, a) == 0 end) |> length() == 1 ->
	  add(x)
	  true
      true -> false
    end
  end

  def isCircularPrime do
    receive do
      x ->
	cond do
	  not isPrime(x) -> false
	  isCircularPrime(x, rotate(Integer.to_string(x), 1)) -> Logger.info("#{x} is circularprime")
	  true -> nil
	end
    end
    isCircularPrime()
  end

  def isCircularPrime(x, y) do
    cond do
      String.to_integer(y) == x -> isPrime(x)
      isPrime(String.to_integer(y)) -> isCircularPrime(x, rotate(y, 1))
      true -> false
    end
  end

  def allCircularPrime() do
    pid = spawn(__MODULE__, :isCircularPrime, [])
    allCircularPrime(pid, 1)
  end
  defp allCircularPrime(_pid, 1000000), do: nil
  defp allCircularPrime(pid, x) do
    send(pid, x)
    allCircularPrime(pid, x+1)
  end

end
