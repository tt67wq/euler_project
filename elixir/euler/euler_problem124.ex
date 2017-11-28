defmodule OrderedRadicals do
  @moduledoc """
  https://projecteuler.net/problem=124
  """

  @doc """
  质因数分解
  """
  @spec factorization(integer) :: map
  def factorization(n), do: fac(n, 2, [])
  defp fac(n, index, acc) when index * index > n and n > 1, do: list2map([n | acc])
  defp fac(n, index, acc) do
    case rem(n, index) == 0 do
      true -> fac(div(n, index), index, [index | acc])
      _ -> fac(n, index + 1, acc)
    end
  end

  def list2map(lst), do: list2map(lst, %{})
  defp list2map([], acc), do: acc
  defp list2map([h|t], acc) do
    case Map.fetch(acc, h) do
      {:ok, c} -> list2map(t, Map.update(acc, h, c, &(&1 + 1)))
      :error -> list2map(t, Map.update(acc, h, 1, &(&1 + 1)))
    end
  end

  def product(list), do: list |> Enum.reduce(1, fn x, acc -> x * acc end)

  def r(1), do: 1
  def r(n), do: factorization(n) |> Map.keys() |> product()

  def solution() do
    1..100000 |> Enum.sort_by(fn x -> r(x) end) |> Enum.at(9999)
  end

  
end
