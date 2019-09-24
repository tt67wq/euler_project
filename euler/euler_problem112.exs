defmodule BouncyNumbers do
  @moduledoc """
  https://projecteuler.net/problem=112
  """
  require Logger

  def int2list(num), do: i2l(num, [])
  defp i2l(0, acc), do: acc
  defp i2l(num, acc), do: i2l(num |> div(10), [num |> rem(10)|acc])

  def bouncy?(num), do: num |> int2list |> bouncy?(nil)
  defp bouncy?([_], :bigger), do: false
  defp bouncy?([_], :smaller), do: false
  defp bouncy?([_], nil), do: false
  defp bouncy?([h1, h2|t], nil) do
    cond do
      h1 > h2 -> bouncy?([h2|t], :bigger)
      h1 < h2 -> bouncy?([h2|t], :smaller)
      :else -> bouncy?([h2|t], :nil)
    end
  end
  defp bouncy?([h1, h2|t], :smaller) when h1 == h2, do: bouncy?([h2|t], :smaller)
  defp bouncy?([h1, h2|t], :smaller) when h1 < h2, do: bouncy?([h2|t], :smaller)
  defp bouncy?([h1, h2|t], :bigger) when h1 == h2, do: bouncy?([h2|t], :bigger)
  defp bouncy?([h1, h2|t], :bigger) when h1 > h2, do: bouncy?([h2|t], :bigger)
  defp bouncy?(_, :bigger), do: true
  defp bouncy?(_, :smaller), do: true


  def solution() do
    sl(100, 0)
  end
  defp sl(index, acc) do
    # Logger.info("index: #{index}, acc: #{acc}")
    cond do
      99 * (index - 1) == acc * 100 -> index - 1
      bouncy?(index) -> sl(index+1, acc+1)
      :else -> sl(index+1, acc)
    end
  end
end
