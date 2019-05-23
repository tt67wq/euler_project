defmodule Euler202 do
  @moduledoc false

  require Integer
  require Logger

  def count2(level), do: count2(level - 3, 3, 0)

  defp count2(level, _row, acc) when level < 0, do: acc

  defp count2(level, row, acc) do
    case rem(level, 2) do
      0 ->
        a = div(level, 2)

        case Integer.gcd(a, level + row - a) do
          1 -> count2(level - 3, row + 3, acc + 1)
          _ -> count2(level - 3, row + 3, acc)
        end

      _ ->
        count2(level - 3, row + 3, acc)
    end
  end

  def run() do
    2 * count2(6_008_819_575)
  end
end
