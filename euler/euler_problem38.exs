defmodule PandigitalMultiples do
  @moduledoc """
  https://projecteuler.net/problem=38
  """
  def concatenated_product(num, n) do
    1..n |> Enum.map(fn x -> x * num end)
    |> list2int()
  end

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
  def get_num_length(num), do: nl(num, 1)
  defp nl(num, acc) do
    case div(num, acc) do
      0 -> acc
      _ -> nl(num, acc * 10)
    end
  end

  @doc """
  ## Example

      iex> Generator.choose([1,2,3], 2)
      [[1, 2], [1, 3], [2, 3]]
  """
  @spec choose(List, Integer) :: List
  def choose(lst, n) when length(lst) == n, do: [lst]
  def choose(lst, 1), do: lst |> Enum.map(fn x -> [x] end)
  def choose([h|t], n), do: (choose(t, n-1) |> Enum.map(fn x -> [h|x] end)) ++ choose(t, n)

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

      iex> digital_mapset(1234)
      #MapSet<[1, 2, 3, 4, 5]>

  """
  def digital_mapset(num), do: dm(num, MapSet.new())
  defp dm(0, acc), do: acc
  defp dm(num, acc), do: dm(div(num, 10), acc |> MapSet.put(rem(num, 10)))

  def solution() do
    choose([1,2,3,4,5,6,7,8], 3)
    |> Enum.map(fn x -> arrange(x) end)
    |> Enum.reduce([], fn x, acc -> x ++ acc end)
    |> Enum.map(fn x -> [9|x] end)
    |> Enum.map(fn x -> list2int(x) end)
    |> Enum.map(fn x -> concatenated_product(x, 2) end)
    |> Enum.filter(fn x -> digital_mapset(x) == MapSet.new([1,2,3,4,5,6,7,8,9]) end)
    |> Enum.max()
  end


end
