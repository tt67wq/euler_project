defmodule Euler181 do
  require Logger

  # defp choose(%{B: 0, W: 0}, acc), do: acc

  defp choose(rest, acc) do
    %{B: b, W: w} = rest

    Enum.map(acc, fn x -> {x, get_candidates(rest, x)} end)
    |> Enum.map(fn {bcc, candidats} -> Enum.map(candidates, fn y -> [y | bcc] end) end)
    |> Enum.concat()
    |> Enum.map()
  end

  defp get_candidates(rest, []) do
    %{B: b, W: w} = rest

    for x <- 0..b,
        y <- 0..w,
        x + y > 0 do
      {x, y}
    end
  end

  defp get_candidates(rest, [{b1, w1} | _t]) do
    %{B: b, W: w} = rest

    for x <- 0..min(b, b1),
        y <- 0..min(w, w1),
        x + y > 0 do
      {x, y}
    end
  end

  def test() do
    choose(%{B: 3, W: 1}, [])
  end
end
