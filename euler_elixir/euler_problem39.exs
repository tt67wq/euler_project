defmodule IntegerRightTriangles do
  @moduledoc """
  If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.
  {20,48,52}, {24,45,51}, {30,40,50}
  For which value of p ≤ 1000, is the number of solutions maximised?
  """
  def right?(a, b, c), do: a * a + b * b == c * c
  def findall(p), do: findall(p, 1, 1, [])
  defp findall(p, a, b, acc) do
    c = p - a - b
    cond do
      c <= a -> acc
      c <= b -> findall(p, a+1, a+2, acc)
      right?(a, b, c) -> findall(p, a, b+1, [{a, b, c} | acc])
      true -> findall(p, a, b+1, acc)
    end
  end

  def max(p), do: max(p, 12, 12, 1)
  defp max(p, c, m, l) when c == p, do: {m, l}
  defp max(p, c, m, l) do
    nl = findall(c) |> length()
    cond do
      nl > l -> max(p, c+1, c, nl)
      true -> max(p, c+1, m, l)
    end
  end



end
