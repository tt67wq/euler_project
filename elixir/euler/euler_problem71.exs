defmodule OrderedFractions do
  @moduledoc """
  https://projecteuler.net/problem=71
  """
  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  def solution(limit), do: sl(limit, limit)

  defp sl(_limit, 0), do: 0
  defp sl(limit, index) do
    x = (index * 3 - 1) |> div(7)
    case gcd(x, index) do
      1 ->
	cond do
	  (3 * index - 7 * x) == 1 -> {x, index}
	  :else -> sl(limit, index - 1)
	end
      _ -> sl(limit, index - 1)
    end
  end
end
