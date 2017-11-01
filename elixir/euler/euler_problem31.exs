defmodule CoinTree do
  @moduledoc """
  In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:

  1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
  It is possible to make £2 in the following way:

  1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
  How many different ways can £2 be made using any number of coins?
  """
  require Logger
  
  defstruct sum: 0, level: 0, value: 0, children: []

  @coin_level %{
    1 => 1,
    2 => 2,
    3 => 5,
    4 => 10,
    5 => 20,
    6 => 50,
    7 => 100,
    8 => 200
  }

  def new(sum), do: %CoinTree{sum: sum, level: 0, value: 0, children: make_children(sum, 0)}

  def make_children(sum, 0), do: make_children(sum, 8)
  def make_children(sum, 1), do: [%CoinTree{sum: sum, level: 1, value: sum, children: []}]
  def make_children(0, _level), do: []
  def make_children(sum, level) do
    amount = Map.fetch!(@coin_level, level)
    Logger.info("amount of level #{level} is #{amount}")
    case div(sum, amount) do
      0 -> make_children(sum, level-1)
      _ -> 0..div(sum, amount) |> Enum.map(fn x -> %CoinTree{sum: sum - amount * x, level: level, value: x, children: make_children(sum - amount * x, level - 1)} end)
    end
  end


  def count(%CoinTree{children: []}), do: 1
  def count(tree), do: count(tree.children, 0)
  defp count([], acc), do: acc
  defp count([h|t], acc), do: count(t, acc + count(h))


end
