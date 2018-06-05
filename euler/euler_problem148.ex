defmodule Euler148 do
  @moduledoc """
  https://projecteuler.net/problem=148
  """
  @limit 1_000_000_000
  require Logger

  def non_multi_base7(n) do
    # Logger.info("#{n}, #{b7(n, 1)}")
    b7(n, 1)
  end

  defp b7(0, acc), do: acc
  defp b7(n, acc), do: b7(div(n, 7), (1 + rem(n, 7)) * acc)

  def solution() do
    r = rem(@limit - 1, 7)
    st = @limit - 1 - r

    s1 =
      0..(div(@limit, 7) - 1)
      |> Enum.map(fn x -> 28 * non_multi_base7(x) end)
      |> Enum.sum()

    Logger.info("胜利在望！")
    s2 =
      st..(@limit - 1)
      |> Enum.map(fn x -> non_multi_base7(x) end)
      |> Enum.sum()

    s1 + s2
  end
end
