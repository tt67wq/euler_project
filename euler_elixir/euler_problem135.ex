defmodule SameDifferences do
  @moduledoc """
  https://projecteuler.net/problem=135
  """
  @limit 1_000_000
  def iter(v), do: iter(v, 1, %{})

  defp iter(v, _, acc) when v > @limit, do: acc
  defp iter(v, u, acc) when u * v > @limit, do: iter(v + 1, 1, acc)
  defp iter(v, u, acc) when u >= 3 * v, do: iter(v + 1, 1, acc)

  defp iter(v, u, acc) do
    case rem(v + u, 4) do
      0 ->
        iter(v, u + 1, Map.update(acc, u * v, 1, fn x -> x + 1 end))

      _ ->
        iter(v, u + 1, acc)
    end
  end

  def solution() do
    sl(iter(1), 1155, 0)
  end

  defp sl(_, index, acc) when index > @limit, do: acc

  defp sl(m, index, acc) do
    c = Map.fetch(m, index)

    case c do
      {:ok, v} ->
        case v do
          10 -> sl(m, index + 1, acc + 1)
          _ -> sl(m, index + 1, acc)
        end

      :error ->
        sl(m, index + 1, acc)
    end
  end
end
