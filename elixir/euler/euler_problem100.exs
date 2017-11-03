defmodule ArrangedProbability do
  @moduledoc """
  If a box contains twenty-one coloured discs, composed of fifteen blue discs and six red discs, 
  and two discs were taken at random, it can be seen that the probability of taking two blue discs, P(BB) = (15/21)×(14/20) = 1/2.
  The next such arrangement, for which there is exactly 50% chance of taking two blue discs at random, 
  is a box containing eighty-five blue discs and thirty-five red discs.
  By finding the first arrangement to contain over 1012 = 1,000,000,000,000 discs in total, 
  determine the number of blue discs that the box would contain.
  """
  # @limit1 1000000000000
  @limit 1000

  require Logger

  def solution() do
    sl(2, 1, 1, 2, 3, [])
  end

  defp sl(x, y, _, _, _, acc) when x > @limit, do: acc
  defp sl(x, _, 0, _, _, acc), do: sl(x+1, 1, x, x+1, x+2, acc)
  defp sl(x, y, t, p, l, acc) do
    # Logger.info("#{x}, #{y}")
    cond do
      1 + 2 * p / t ==  l ->
	Logger.info("#{x}, #{y}")
	sl(x, y + 1, t - 1, x * (y + 1), l+1, [{x,y}|acc])
      :else -> sl(x, y + 1, t - 1, x * (y + 1), l+1, acc)
    end
  end



end
