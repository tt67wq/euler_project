defmodule Euler181 do
  ## 83735848679360670
  require Logger

  defp search(%{B: 0, W: 0}, _), do: 1

  defp search(rest, {bh, _wh} = head) do
    # Logger.info("#{inspect(rest)}, #{bh}, #{wh}")
    %{B: b, W: w} = rest

    case :ets.lookup(:euler181, finger_print(rest, head)) do
      [{_, v}] ->
        v

      _ ->
        v =
          for x <- 0..min(b, bh),
              y <- 0..w,
              x + y > 0 do
            {x, y}
          end
          |> Enum.filter(fn x -> less_equal(x, head) end)
          |> Enum.map(fn {x, y} -> search(%{B: b - x, W: w - y}, {x, y}) end)
          |> Enum.sum()

        :ets.insert(:euler181, {finger_print(rest, head), v})
        v
    end
  end

  defp less_equal({a, _b}, {c, _d}) when a < c, do: true
  defp less_equal({a, b}, {a, d}) when b <= d, do: true
  defp less_equal(_, _), do: false

  defp finger_print(rest, {bh, wh}) do
    %{B: b, W: w} = rest
    "#{b}:#{w}:#{bh}:#{wh}"
  end

  def init(), do: :ets.new(:euler181, [:named_table])

  def run() do
    search(%{B: 60, W: 40}, {60, 40})
  end
end
