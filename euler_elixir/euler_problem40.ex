defmodule Euler40 do
  @moduledoc """
  https://projecteuler.net/problem=40
  """
  require Logger

  def num_len(num), do: len(num, 0)
  defp len(0, acc), do: acc
  defp len(num, acc), do: len(div(num, 10), acc + 1)

  def num2list(num), do: n2l(num, [])
  defp n2l(0, acc), do: acc
  defp n2l(num, acc), do: n2l(div(num, 10), [rem(num, 10) | acc])

  def offset(num, index), do: num2list(num) |> Enum.at(index)

  defp now(), do: :os.system_time(:micro_seconds)

  def run() do
    start = now()
    anchors = [1, 10, 100, 1000, 10000, 100_000, 1_000_000]

    result =
      iter(1, 1, 1, anchors, [])
      |> Enum.reduce(1, fn x, acc -> x * acc end)

    timeuse = now() - start
    IO.puts("result => #{result}, timeuse => #{timeuse} microseconds")
  end

  defp iter(_, _, _, [], acc), do: acc

  defp iter(si, ei, index, [h | t] = anchors, acc) do
    l = num_len(index)

    cond do
      h >= si and h < ei ->
        # Logger.info(
        #   "[#{si}, #{ei}), num: #{index - 1}, offset: #{h - si}, digit : #{
        #     offset(index - 1, h - si)
        #   }"
        # )

        iter(ei, ei + l, index + 1, t, [offset(index - 1, h - si) | acc])

      :else ->
        iter(ei, ei + l, index + 1, anchors, acc)
    end
  end
end
