defmodule ArrangedProbability do
  @moduledoc """
  If a box contains twenty-one coloured discs, composed of fifteen blue discs and six red discs, 
  and two discs were taken at random, it can be seen that the probability of taking two blue discs, P(BB) = (15/21)×(14/20) = 1/2.
  The next such arrangement, for which there is exactly 50% chance of taking two blue discs at random, 
  is a box containing eighty-five blue discs and thirty-five red discs.
  By finding the first arrangement to contain over 1012 = 1,000,000,000,000 discs in total, 
  determine the number of blue discs that the box would contain.

  计算2x(x-1) = y(y-1) 其中xs蓝色数量，y是周长
  得出方程 2x^2-y^2-2x+y = 0
  根据http://www.alpertron.com/CUAD.HTM
  算出递归公式

  Xn+1 = P Xn + Q Yn + K
  Yn+1 = R Xn + S Yn + L

  P = 3
  Q = 2
  K = -2
  R = 4
  S = 3
  L = -3

  Xn+1 = 3Xn + 2Yn - 2
  Yn+1 = 4Xn + 3Yn - 3

  x1 = 1
  y1 = 1
  """
  @limit 1_000_000_000_000

  require Logger

  def iter(x, y), do: {3 * x + 2 * y - 2, 4 * x + 3 * y - 3}

  def solution() do
    sl(1, 1)
  end

  defp sl(x, y) when y > @limit, do: {x, y}

  defp sl(x, y) do
    {x1, y1} = iter(x, y)
    sl(x1, y1)
  end
end
