defmodule PentagonNumbers do
  @moduledoc """
  https://projecteuler.net/problem=44
  """
  defp now(), do: :os.system_time(:milli_seconds)

  @spec pentagon(Integer) :: Integer
  def pentagon(n), do: div(n * (3 * n - 1), 2)

  def run() do
    start = now()
    res = find(1, [], [])
    timeuse = now() - start
    IO.puts("result ==> #{res}, timeuse ==> #{timeuse} milliseconds")
  end

  defp find(index, [], acc) do
    nacc = [pentagon(index + 1) | acc]
    find(index + 1, Enum.reverse(nacc), nacc)
  end

  defp find(index, [h | t], acc) do
    p = pentagon(index)

    cond do
      acc |> Enum.member?(p - h) and acc |> Enum.member?(p - h * 2) -> p - h * 2
      :else -> find(index, t, acc)
    end
  end
end
