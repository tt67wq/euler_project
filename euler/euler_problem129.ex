defmodule RepunitDivisibility do
  @moduledoc """
  https://projecteuler.net/problem=129
  """
  require Integer
  require Logger
  @limit 1_000_000

  def r(n), do: r(n, 1, 1)
  defp r(n, index, acc) when index == n, do: acc
  defp r(n, index, acc), do: r(n, index + 1, acc * 10 + 1)

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

  def func(n), do: r(n) |> factorization()

  def a(n) do
    a(n, length(Integer.digits(n)))
  end

  defp a(n, index) do
    case rem(r(index), n) do
      0 -> index
      _ -> a(n, index + 1)
    end
  end

  def solution() do
    sl(3)
  end

  defp sl(index) do
    case rem(index, 5) do
      0 ->
        sl(index + 2)

      _ ->
        an = a(index)

        cond do
          an > @limit ->
            index

          :else ->
            Logger.info("A(#{index}) is #{an}")
            sl(index + 2)
        end
    end
  end
end
