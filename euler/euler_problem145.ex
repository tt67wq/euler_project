defmodule Euler145 do
  @moduledoc """
  https://projecteuler.net/problem=145
  """
  require Integer
  require Logger

  def solution, do: sl(1, 0)

  def pow(a, b), do: :math.pow(a, b) |> round()

  defp sl(index, acc) when index > 9, do: acc

  defp sl(index, acc) do
    Logger.info("#{index}, #{acc}")

    case rem(index, 4) do
      0 -> sl(index + 1, acc + 20 * pow(30, div(index, 2) - 1))
      1 -> sl(index + 1, acc)
      2 -> sl(index + 1, acc + 20 * pow(30, div(index, 2) - 1))
      3 -> sl(index + 1, acc + 100 * pow(500, div(index, 4)))
    end
  end
end
