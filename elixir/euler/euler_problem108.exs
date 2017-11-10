defmodule DiophantineReciprocals do
  @moduledoc """
  https://projecteuler.net/problem=108
  The equation is equivalent to z=xyx+y. Let d=gcd(x,y). Then

  x=dm, y=dn, with gcd(m,n)=1.

  It follows that gcd(mn,m+n)=1 so that

  z=dmnm+n,

  which implies (m+n)|d, i.e., d=k(m+n), k a positive integer.

  Thus we obtain the solutions:

  x=km(m+n), y=kn(m+n), z=kmn,

  where the three parameters k,m,n are positive integers.
  """
  @limit 1000
  require Logger

  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

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

  def add(a, b), do: a + b

  @doc """
  ## Example

      iex> Generator.choose([1,2,3], 2)
      [[1, 2], [1, 3], [2, 3]]
  """
  @spec choose(List, Integer) :: List
  def choose(lst, n), do: chs(lst, n) |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end) |> MapSet.to_list()
  defp chs(lst, n) when length(lst) == n, do: [lst]
  defp chs(lst, 1), do: lst |> Enum.map(fn x -> [x] end)
  defp chs([h|t], n), do: (choose(t, n-1) |> Enum.map(fn x -> [h|x] end)) ++ choose(t, n)


  @doc """
  将list分割成2份可能性
  ## Example

      iex> list_split([1, 2, 3])
      [[[1, 2], [3]], [[1, 3], [2]], [[2, 3], [1]]]

  """
  def list_cut(list), do: lc(list, 1, [])
  defp lc(list, count, acc) when count * 2 > length(list), do: acc
  defp lc(list, count, acc) do
    nacc = acc ++ choose(list, count)
    |> Enum.map(fn x -> [x, list_sub(list, x)]
    |> Enum.sort end)
    |> MapSet.new()
    |> MapSet.to_list
    lc(list, count+1, nacc)
  end
  defp list_sub(list1, list2), do: list1 |> Enum.filter(fn x -> not Enum.member?(list2, x) end)


  @doc """
  将num分解成互质的两个数乘积的可能
  """
  def get_rprime(num) do
    ls = num |> factorization
    |> Map.keys
    |> list_cut
    [[[1], [num]]|ls]
  end

  def get_all_facs(num), do: gaf(num, 1, [])
  defp gaf(num, index, acc) when index * 2 > num, do: [num|acc]
  defp gaf(num, index, acc) do
    cond do
      rem(num, index) == 0 -> gaf(num, index+1, [index|acc])
      :else -> gaf(num, index+1, acc)
    end
  end

  def calculate_all(num) do
    num |> get_all_facs
    |> Enum.filter(fn x -> x != 1 end)
    |> Enum.map(fn x -> x |> get_rprime |> length end)
    |> Enum.sum()
    |> add(1)
  end
end
