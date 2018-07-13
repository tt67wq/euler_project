defmodule Euler do
  @moduledoc """
  A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:
  1/2	= 	0.5
  1/3	= 	0.(3)
  1/4	= 	0.25
  1/5	= 	0.2
  1/6	= 	0.1(6)
  1/7	= 	0.(142857)
  1/8	= 	0.125
  1/9	= 	0.(1)
  1/10	= 	0.1
  Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

  Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
  """
  require Logger
  def cycle(n), do: cycle(n, 0, 1, [])
  defp cycle(n, d, r, acc) do
    # Logger.info fn -> inspect {d, r} end
    # Logger.info fn -> inspect(acc) end
    cond do
      Enum.member?(acc, {d, r}) -> acc
      true -> _cycle(n, d, r, acc)
    end
  end

  defp _cycle(_n, d, 0, acc), do: [{d, 0} | acc]
  defp _cycle(n, 0, r, acc), do: cycle(n, div(r * 10, n), rem(r * 10, n), acc)
  defp _cycle(n, d, r, acc), do: cycle(n, div(r * 10, n), rem(r * 10, n), [{d, r} | acc])

  def longest_util(n), do: util(n, 1, 1, 1)
  defp util(n, n, _l, max), do: max
  defp util(n, index, l, max) do
    nl = cycle(index) |> length()
    cond do
      nl > l -> util(n, index+1, nl, index)
      true -> util(n, index+1, l, max)
    end
  end

end
