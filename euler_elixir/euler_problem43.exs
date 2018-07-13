defmodule SubStringdivisibility do
  @moduledoc """
  https://projecteuler.net/problem=43
  """
  require Logger
  @primes [2, 3, 5, 7, 11, 13, 17]
  
  @doc """
  ## Example
  
      iex> Generator.arrange([1, 2, 3])
      [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
  """
  @spec arrange(List) :: List
  def arrange(lst) when length(lst) == 1, do: [lst]
  def arrange([h|t]), do: arrange(t) |> Enum.reduce([], fn x, acc -> insert(h, x) ++ acc end)
  def insert(n, lst), do: 0..length(lst) |> Enum.map(fn x -> List.insert_at(lst, x, n) end)

  @doc """
  ## Example

      iex> list2int([12,23,123])
      1223123
  """
  def list2int(lst), do: l2i(lst, 0)
  defp l2i([], acc), do: acc
  defp l2i([h|t], acc), do: l2i(t, get_num_length(h) * acc + h)

  @doc """
  ## Example

      iex> get_num_length(99)
      100
      iex> get_num_length(123)
      1000

  """
  def get_num_length(0), do: 10
  def get_num_length(num), do: nl(num, 1)
  defp nl(num, acc) do
    case div(num, acc) do
      0 -> acc
      _ -> nl(num, acc * 10)
    end
  end

  def satisfy(num), do: satisfy(num, 0)
  defp satisfy(_num, 7), do: true
  defp satisfy(num, index) do
    # Logger.info("#{num}, #{index}")
    d = :math.pow(10, (6 - index)) |> round()
    a = num |> div(d) |> rem(1000)
    case rem(a, Enum.at(@primes, index)) do
      0 -> satisfy(num, index + 1)
      _ -> false
    end
  end

  def solution() do
    arrange([0,1,2,3,4,5,6,7,8,9])
    |> Enum.map(fn x -> list2int(x) end)
    |> Enum.filter(fn x -> satisfy(x) end)
    |> Enum.sum()
  end
end
