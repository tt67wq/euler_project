defmodule Euler169 do
  @moduledoc """
  https://projecteuler.net/problem=169
  """

  require Integer

  defp starts_with_0?([]), do: true
  defp starts_with_0?([h | _]), do: h == 0

  defp ends_with_0?([]), do: true

  defp ends_with_0?(list) do
    [h | _] = Enum.reverse(list)
    h == 0
  end

  def split(list) do
    0..Enum.count(list)
    |> Enum.map(fn x -> Enum.split(list, x) end)
    |> Enum.filter(fn {h, _t} -> ends_with_0?(h) end)
    |> Enum.filter(fn {_h, t} -> not starts_with_0?(t) end)
  end

  defp iter([h]), do: [h]

  defp iter([a, b | t]) do
    case a do
      0 ->
        [0 | iter([b | t])]

      _ ->
        case b do
          0 -> [a - 1, 2 | t]
          _ -> [a | iter([b | t])]
        end
    end
  end

  def cluster(list), do: get_cluster(list, [])

  defp get_cluster(list, acc) do
    cond do
      Enum.member?(acc, list) -> acc
      :else -> get_cluster(iter(list), [list | acc])
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
    # |> decimal2binary()
    # |> split()
    # |> Enum.map(fn {h, t} -> {h, cluster(t)} end)
    # |> Enum.reduce([], fn {h, c}, acc -> acc ++ Enum.map(c, fn x -> h ++ x end) end)
    # |> Enum.uniq()
    # |> Enum.count()
  end
end
