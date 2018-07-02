defmodule Euler152 do
  @moduledoc """
  https://projecteuler.net/problem=152
  """
  require Logger

  @type int :: non_neg_integer
  @type ints :: [int]

  @base nums = [
          2,
          3,
          4,
          5,
          6,
          7,
          8,
          9,
          10,
          12,
          14,
          15,
          16,
          18,
          20,
          21,
          24,
          25,
          27,
          28,
          30,
          32,
          35,
          36,
          40,
          42,
          45
        ]

  @lcm 4_480_842_240_000

  @inverse @base |> Enum.map(fn x -> div(@lcm, x) end)

  @spec find(int, int, ints) :: ints
  defp find(0, _index, acc), do: acc

  defp find(remainder, index, acc) do
    new_remainder = remainder - Enum.at(@inverse, index)
  end
end
