defmodule Euler169 do
  @moduledoc """
  https://projecteuler.net/problem=169
  """

  require Integer
  require Logger

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
    cluster_iter(1, acc, acc)
  end

  defp cluster_iter(index, bcc, acc) do
    # Logger.info(index)

    nbcc =
      bcc
      |> Enum.map(fn x -> get_cluster(x, index, []) end)
      |> Enum.filter(fn x -> Enum.count(x) > 1 end)
      |> Enum.reduce([], fn x, cc -> x ++ cc end)

    cond do
      Enum.count(nbcc) == 0 -> acc
      :else -> cluster_iter(index + 1, nbcc, nbcc ++ acc)
    end
  end

  defp get_cluster(list, index, acc) do
    next = iter(list, index)

    cond do
      next == list -> [list | acc]
      :else -> get_cluster(next, index, [list | acc])
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
    # pow(10, x)
    decimal2binary(x)
    |> cluster()
    |> Enum.uniq()
    |> Enum.count()
  end
end
