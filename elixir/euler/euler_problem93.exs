defmodule ArithmeticExpressions do
  @moduledoc """
  https://projecteuler.net/problem=93
  """

  @limit 9
  require Logger

  def combine2(a, b), do: [a + b, a - b, b - a, a * b, a / b, b / a] |> Enum.filter(fn x -> x > 0 end)
  def combine3(a, b, c) do
    combine2(a, b) |> Enum.map(fn x -> combine2(x, c) end)
    |> concat(combine2(a, c) |> Enum.map(fn x -> combine2(x, b) end))
    |> concat(combine2(b, c) |> Enum.map(fn x -> combine2(x, a) end))
    |> List.flatten
    |> Enum.sort()
    |> Enum.dedup()
  end

  def combine4_1(a, b, c, d) do
    xs = combine2(a, b)
    ys = combine2(c, d)
    l1 = for x <- xs,
      y <- ys do
	combine2(x, y)
    end
    |> List.flatten()
    |> Enum.sort()
    |> Enum.dedup()

    xs = combine2(a, c)
    ys = combine2(b, d)
    l2 = for x <- xs,
      y <- ys do
	combine2(x, y)
    end
    |> List.flatten()
    |> Enum.sort()
    |> Enum.dedup()

    xs = combine2(a, c)
    ys = combine2(b, d)
    l3 = for x <- xs,
      y <- ys do
	combine2(x, y)
    end
    |> List.flatten()
    |> Enum.sort()
    |> Enum.dedup()

    l1 ++ l2 ++ l3
    |> List.flatten()
    |> Enum.sort()
    |> Enum.dedup()
  end

  def combine4_2(a, b, c, d) do
    l1 = combine3(a, b, c) |> Enum.map(fn x -> combine2(x, d) end)
    l2 = combine3(a, b, d) |> Enum.map(fn x -> combine2(x, c) end)
    l3 = combine3(a, c, d) |> Enum.map(fn x -> combine2(x, b) end)
    l4 = combine3(b, c, d) |> Enum.map(fn x -> combine2(x, a) end)
    l1 ++ l2 ++ l3 ++ l4
    |> List.flatten()
    |> Enum.sort()
    |> Enum.dedup()
  end

  def combine4(a, b, c, d) do
    combine4_1(a, b, c, d) ++ combine4_2(a, b, c, d)
    |> List.flatten()
    |> Enum.filter(fn x -> is_int?(x) end)
    |> Enum.map(fn x -> x |> round end)
    |> Enum.sort()
    |> Enum.dedup()
  end

  def consecutive_util(list), do: cu(list, 1)
  defp cu([], index), do: index
  defp cu([h|_t], index) when h != index, do: index
  defp cu([index|t], index), do: cu(t, index + 1)

  def is_int?(num), do: num == num |> round()
  
  def concat(list1, list2), do: list1 ++ list2

  def solution() do
    sl(1, 2, 3, 4, {29, [1,2,3,4]})
  end

  defp sl(1, 2, 3, d, acc) when d == @limit, do: acc
  defp sl(1, 2, c, d, acc) when c == d, do: sl(1, 2, 3, d + 1, acc)
  defp sl(1, b, c, d, acc) when b == c, do: sl(1, 2, c + 1, d, acc)
  defp sl(a, b, c, d, acc) when a == b, do: sl(1, b + 1, c, d, acc)
  defp sl(a, b, c, d, {acc, list}) do
    Logger.info("now max is #{acc}, #{inspect list}")
    cb = combine4(a, b, c, d)
    u = cb |> consecutive_util()
    # Logger.info("all combine of #{inspect [a, b, c, d]} is #{inspect cb}")
    Logger.info("max combine of #{inspect [a, b, c, d]} is #{u}")
    cond do
      u > acc -> sl(a+1, b, c, d, {u, [a, b, c, d]})
      :else -> sl(a+1, b, c, d, {acc, list})
    end
  end
end
