defmodule PowerfulDigitCounts do
  @moduledoc """
  The 5-digit number, 16807=75, is also a fifth power. Similarly, the 9-digit number, 134217728=89, is a ninth power.

  How many n-digit positive integers exist which are also an nth power?

  分析

  假设一个位数为x的数S=kx,得到关系式：

  

  右端可得：1<=k<=9

  左端看得：k>=101-1/x,

  题目的解就是统计满足上面不等式的k值的总数。


  """
  require Logger

  def range(x), do: {:math.pow(10, 1 - 1/x), 9}

  def solution(), do: s(1, 0)
  defp s(index, acc) do
    {b, _} = range(index)
    cond do
      b - round(b) > 0 ->
	k = round(b) + 1
	Logger.info("#{k}")
	cond do
	  k > 9 -> acc
	  :eles -> s(index+1, acc + 9 - k + 1)
	end
      :else ->
	k = round(b)
	Logger.info("#{k}")
	cond do
	  k > 9 -> acc
	  :eles -> s(index+1, acc + 9 - k + 1)
	end
    end

  end
end
