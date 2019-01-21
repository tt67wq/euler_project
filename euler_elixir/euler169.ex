defmodule Euler169 do
  @moduledoc """
  https://projecteuler.net/problem=169
  """

  require Integer

  defp iter([], _), do: []
  defp iter([h], _), do: [h]

  defp iter([a, b | t], index) do
    case a do
      0 ->
        [0 | iter([b | t], index)]

      _ ->
        case b do
          0 ->
            case index do
              0 -> [a - 1, 2 | t]
              _ -> [a | iter([b | t], index - 1)]
            end

          _ ->
            [a | iter([b | t], index)]
        end
    end
  end

  def cluster(list) do
    acc = get_cluster(list, 0, [])
    cluster(1, acc)
  end

  defp cluster(index, acc) do
    nacc =
      Enum.reduce(acc, [], fn x, bcc -> bcc ++ get_cluster(x, index, []) end)
      |> Enum.uniq()

    cond do
      Enum.count(nacc) == Enum.count(acc) -> acc
      :else -> cluster(index + 1, nacc)
    end
  end

  defp get_cluster(list, index, acc) do
    cond do
      Enum.member?(acc, list) -> acc
      :else -> get_cluster(iter(list, index), index, [list | acc])
    end
  end

  def pow(_, 0), do: 1
  def pow(x, n) when Integer.is_odd(n), do: x * pow(x, n - 1)

  def pow(x, n) do
    result = pow(x, div(n, 2))
    result * result
  end

  def decimal2binary(num), do: d2b(num, [])
  defp d2b(0, acc), do: acc
  defp d2b(num, acc), do: d2b(div(num, 2), [rem(num, 2) | acc])

  def run(x) do
    pow(10, x)
    |> decimal2binary()
    |> cluster()
    # |> Enum.uniq()
    |> Enum.count()
  end
end
