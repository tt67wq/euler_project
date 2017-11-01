defmodule NonabundantSums do
  @moduledoc """
  A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. 
  For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

  A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

  As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24.
  By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers.
  However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

  Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
  """
  use GenServer
  require Logger

  @spec factorization(integer) :: map
  def factorization(n), do: fac(n, 2, [])
  defp fac(n, index, acc) when index * index > n and n > 1 do
    # Logger.info("final: #{n}, #{index}")
    list2map([n | acc])
  end
  defp fac(n, index, acc) do
    # Logger.info("#{n}, #{index}")
    case rem(n, index) == 0 do
      true -> fac(div(n, index), index, [index | acc])
      _ -> fac(n, index + 1, acc)
    end
  end

  def is_prime(x), do: (2..x |> Enum.filter(fn a -> rem(x, a) == 0 end) |> length()) == 1

  def list2map(lst), do: list2map(lst, %{})
  defp list2map([], acc), do: acc
  defp list2map([h|t], acc) do
    case Map.fetch(acc, h) do
      {:ok, c} -> list2map(t, Map.update(acc, h, c, &(&1 + 1)))
      :error -> list2map(t, Map.update(acc, h, 1, &(&1 + 1)))
    end
  end

  def sum_of_divisors(n), do: sum(Map.to_list(factorization(n)), 1)
  defp sum([], acc), do: acc
  defp sum([{a, b} | t], acc) do
    # Logger.info("#{a} #{b}")
    sum(t, acc * _sum(a, b, 0))
  end
  defp _sum(_a,  0, acc), do: acc + 1
  defp _sum(a, index, acc) do
    _sum(a, index - 1, acc + :math.pow(a, index))
  end


  def init(state), do: {:ok, state}

  def handle_call({:abundant, n}, _from, state) do
    case Enum.member?(state, n) do
      true -> {:reply, true, state}
      _ ->
	a = _abundant?(n)
	if a do
	  Logger.info("#{n} is abundant")
	  {:reply, a, [n | state]}
	else
	  {:reply, false, state}
	end
    end
  end

  def start_link(state \\ []) do
    GenServer.start_link(__MODULE__, state, name: __MODULE__)
  end

  def abundant?(n), do: GenServer.call(__MODULE__, {:abundant, n})

  defp _abundant?(n) do
    sum_of_divisors(n) > 2 * n
  end


  def sum_of_2_abundant?(1), do: false
  def sum_of_2_abundant?(number), do: sum_of_2_abundant?(number, 2)
  defp sum_of_2_abundant?(number, index) when index > div(number, 2), do: false
  defp sum_of_2_abundant?(number, index) do
    case abundant?(index) and abundant?(number-index) do
      true -> true
      false -> sum_of_2_abundant?(number, index+1)
    end
  end

  def non_abundant_sums(n), do: 1..n |> Enum.filter(fn x -> not sum_of_2_abundant?(x) end) |> Enum.sum()
end
