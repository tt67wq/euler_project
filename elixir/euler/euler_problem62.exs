defmodule CubicPermutations do
  @moduledoc """
  The cube, 41063625 (3453), can be permuted to produce two other cubes: 56623104 (3843) and 66430125 (4053).
  In fact, 41063625 is the smallest cube which has exactly three permutations of its digits which are also cube.
  Find the smallest cube for which exactly five permutations of its digits are cube.
  """
  def cube(n), do: n * n * n
  def cube_set(n), do: cube(n) |> Integer.to_charlist() |> Enum.sort()

  def solution(), do: s(345, %{})
  defp s(index, acc) do
    m = cube_set(index)
    case Map.fetch(acc, m) do
      {:ok, lst} ->
	cond do
	  length([index|lst]) == 5 -> [index|lst]
	  :else -> s(index + 1, Map.update!(acc, m, fn _ -> [index|lst] end))
	end
      :error -> s(index + 1, Map.put(acc, m, [index]))
    end
  end
  
end
