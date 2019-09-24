defmodule Euler206 do
  @moduledoc false

  # 1_2_3_4_5_6_7_8_9_0
  @low 1_010_101_010

  def check(num), do: check(num, [0, 9, 8, 7, 6, 5, 4, 3, 2, 1])

  defp check(_, []), do: true

  defp check(num, [h | t]) do
    case rem(num, 10) do
      ^h -> check(div(num, 100), t)
      _ -> false
    end
  end

  defp iter(index) do
    case check(index * index) do
      true -> index
      _ -> iter(index + 10)
    end
  end

  def run() do
    iter(@low)
  end
end
