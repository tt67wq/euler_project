defmodule ChangeCoin do
  @moduledoc """
  给出不同面额的硬币以及一个总金额.
  计算给出的总金额可以换取的最少的硬币数量
  """

  def init() do
    :ets.new(:coin, [:named_table])
  end

  ## 求用coins换amount面值所用最小的数量的组合
  defp change(amount, _) when amount < 0, do: nil
  defp change(0, _), do: []

  defp change(amount, coins) do
    case :ets.lookup(:coin, amount) do
      [{_, v}] ->
        v

      [] ->
        {coin, v} =
          Enum.map(coins, fn x -> {x, change(amount - x, coins)} end)
          |> Enum.filter(fn {_, x} -> x != nil end)
          |> Enum.min_by(fn {_, x} -> Enum.count(x) end)

        :ets.insert(:coin, {amount, [coin | v]})
        [coin | v]
    end
  end

  def run() do
    change(13, [5, 2, 1])
  end
end
