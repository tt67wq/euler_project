defmodule OptimumPolynomial do
  @moduledoc """
  https://projecteuler.net/problem=101
  un = 1 − n + n2 − n3 + n4 − n5 + n6 − n7 + n8 − n9 + n10
  [1, 683, 44287, 838861, 8138021, 51828151, 247165843, 954437177, 3138105961, 9090909091]
  可以根据牛顿级数来解决这个问题
  """

  @base [
    1,
    683,
    44287,
    838_861,
    8_138_021,
    51_828_151,
    247_165_843,
    954_437_177,
    3_138_105_961,
    9_090_909_091
  ]
  # @base [1, 8, 27, 64, 125, 216]

  def pow(a, b), do: :math.pow(a, b) |> round()

  def factorial(n), do: fac(n, 1)
  defp fac(0, acc), do: acc
  defp fac(n, acc), do: fac(n - 1, acc * n)

  def u(n),
    do:
      1 - n + pow(n, 2) - pow(n, 3) + pow(n, 4) - pow(n, 5) + pow(n, 6) - pow(n, 7) + pow(n, 8) -
        pow(n, 9) + pow(n, 10)

  def delta(list), do: delta(list, [])
  defp delta([h1, h2], acc), do: [h2 - h1 | acc] |> Enum.reverse()
  defp delta([h1, h2 | t], acc), do: delta([h2 | t], [h2 - h1 | acc])

  def get_k_series(list, 0), do: [list |> List.first()]
  def get_k_series(list, k), do: [list |> List.first() | get_k(list, k, [])]
  defp get_k(_, 0, acc), do: acc |> Enum.reverse()

  defp get_k(list, k, acc) do
    dlist = delta(list)
    get_k(dlist, k - 1, [dlist |> List.first() | acc])
  end

  def fac_x(x, k), do: fac_x(x, k, 1, 1)
  defp fac_x(_x, k, index, acc) when index > k, do: div(acc, factorial(k))
  defp fac_x(x, k, index, acc), do: fac_x(x, k, index + 1, (x - index) * acc)

  def op(series, k, x), do: op(series, k, x, 0, 0)
  defp op(_, k, _, index, acc) when index > k, do: acc
  defp op([h | t], k, x, index, acc), do: op(t, k, x, index + 1, h * fac_x(x, index) + acc)

  def solution() do
    series = get_k_series(@base, 9)
    0..9 |> Enum.map(fn x -> op(series, x, x + 2) end)
  end
end
