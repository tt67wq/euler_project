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

  def real(x) do
    decimal2binary(x)
    |> cluster()
    |> Enum.uniq()
    |> Enum.count()
  end

  defp get_d(0), do: 0
  defp get_d(1), do: 1

  defp get_d(n) do
    case :ets.lookup(:euler169, n) do
      [{_, v}] ->
        v

      [] ->
        k = div(get_d(n - 2), get_d(n - 1))
        v = (2 * k + 1) * get_d(n - 1) - get_d(n - 2)
        :ets.insert(:euler169, {n, v})
        v
    end
  end

  def f(x) when x < 100, do: real(x)

  def f(x) do
    case :ets.lookup(:euler169_2, x) do
      [{_, v}] ->
        v

      [] ->
        Logger.info(x)

        v =
          cond do
            rem(x, 2) == 0 ->
              y = div(x, 2)
              f(y) + f(y - 1)

            :else ->
              y = div(x - 1, 2)
              f(x - 1) - get_d(y)
          end

        :ets.insert(:euler169_2, {x, v})
        v
    end
  end

  def run() do
    :ets.new(:euler169, [:named_table])
    :ets.new(:euler169_2, [:named_table])

    pow(10, 25)
    |> f()
  end
end
