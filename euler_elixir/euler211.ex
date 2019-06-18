defmodule Euler211 do
  @moduledoc false

  @top 64_000_000
  # @top 100

  require Logger

  def init, do: :ets.new(:euler211, [:named_table])

  def pre() do
    1..@top
    |> Enum.each(fn
      1 -> :ets.insert(:euler211, {1, 1})
      x -> :ets.insert(:euler211, {x, x * x + 1})
    end)
  end

  defp iter0(index) when index * 2 > @top, do: :ok

  defp iter0(index) do
    # Logger.info(index)
    :ok = iter1(index, index * 2)
    iter0(index + 1)
  end

  defp iter1(_k, index) when index > @top, do: :ok

  defp iter1(k, index) do
    [{_, v}] = :ets.lookup(:euler211, index)
    :ets.insert(:euler211, {index, v + k * k})
    iter1(k, index + k)
  end

  defp perfect_sqrt?(x) do
    sq = :math.sqrt(x) |> round
    sq * sq == x
  end

  def test do
    init()
    pre()
    :ok = iter0(2)

    1..@top
    |> Enum.map(fn x -> :ets.lookup(:euler211, x) end)
    |> Enum.filter(fn [{_, v}] -> perfect_sqrt?(v) end)
    |> Enum.map(fn [{x, _}] -> x end)
  end
end
