defmodule Euler201 do
  @moduledoc false

  require Logger

  @pool 1..100 |> Enum.map(fn x -> x * x end)

  defp iter(_, [t], acc), do: Enum.reverse([t | acc])

  defp iter(n, [mp1, mp2 | t], acc) do
    nmp1 =
      Map.to_list(mp2)
      |> Enum.map(fn {k, v} -> {k + n, v} end)
      |> Enum.reduce(mp1, fn {x, v}, acc ->
        Map.update(
          acc,
          x,
          if v == 2 do
            2
          else
            1
          end,
          fn _ -> 2 end
        )
      end)

    iter(n, [mp2 | t], [nmp1 | acc])
  end

  def run do
    state = [%{0 => 0} | List.duplicate(%{}, 50)] |> Enum.reverse()

    @pool
    |> Enum.reduce(state, fn x, acc -> iter(x, acc, []) end)
    |> List.first()
    |> Map.to_list()
    |> Enum.filter(fn {_k, v} -> v == 1 end)
    |> Enum.map(fn {k, _v} -> k end)
    |> Enum.sum()
  end
end
