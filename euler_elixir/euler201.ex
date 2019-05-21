defmodule Euler201 do
  @moduledoc false

  @pool 1..50 |> Enum.map(fn x -> x * x end)

  def count_path(num), do: cpath(num, 0, [], 0)

  defp cpath(num, 50, _, bcc) when bcc == num, do: 1
  defp cpath(_, 50, _, _), do: 0

  defp cpath(num, index, acc, bcc) do
    @pool
    |> Enum.filter(fn x -> not Enum.member?(acc, x) end)
    |> Enum.filter(fn x -> x + bcc <= num end)
    |> Enum.map(fn x -> cpath(num, index + 1, [x | acc], bcc + x) end)
    |> Enum.sum()
  end

  def run do
    @pool
  end
end
