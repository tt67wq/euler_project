defmodule Euler152 do
  @moduledoc """
  https://projecteuler.net/problem=152
  """
  require Logger

  @type int :: non_neg_integer
  @type ints :: [int]

  @base [
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
    45,
    48,
    49,
    50,
    54,
    56,
    60,
    63,
    64,
    70,
    72,
    75,
    80
  ]

  @lcm 4_480_842_240_000

  @inverse @base |> Enum.map(fn x -> div(@lcm, x * x) end)

  @spec bfs(int, ints) :: [ints]
  defp bfs(0, _list), do: [[]]
  defp bfs(_, []), do: []

  defp bfs(r, [h | t]) do
    nr = r - h

    cond do
      nr < 0 ->
        bfs(r, t)

      :else ->
        case bfs(nr, t) do
          [] ->
            bfs(r, t)

          vs ->
            Enum.map(vs, fn x -> [h | x] end) ++ bfs(r, t)
        end
    end
  end

  defp sqrt(x), do: :math.sqrt(x) |> round()

  def solution() do
    trans = fn list -> Enum.map(list, fn x -> div(@lcm, x) |> sqrt() end) end

    bfs(div(@lcm, 2), @inverse)
    |> Enum.map(trans)
  end
end
