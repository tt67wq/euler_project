defmodule DiscGamePrizeFund do
  @moduledoc """
  https://projecteuler.net/problem=121

  A bag contains one red disc and one blue disc. In a game of chance a player takes a disc at random and its colour is noted.
  After each turn the disc is returned to the bag, an extra red disc is added, and another disc is taken at random.

  The player pays £1 to play and wins if they have taken more blue discs than red discs at the end of the game.

  If the game is played for four turns, the probability of a player winning is exactly 11/120, 
  and so the maximum prize fund the banker should allocate for winning in this game would be £10 before they would expect to incur a loss.
  Note that any payout will be a whole number of pounds and also includes the original £1 paid to play the game,
  so in the example given the player actually wins £9.
  Find the maximum prize fund that should be allocated to a single game in which fifteen turns are played.
  """
  @init [:r, :b]
  @round 15
  require Logger

  def play_once(discs), do: {Enum.random(discs), [:r|discs]}

  def play(), do: play(1, @init, [])
  defp play(r, _, acc) when r > @round, do: acc
  defp play(r, bcc, acc) do
    {c, nbcc} = play_once(bcc)
    play(r+1, nbcc, [c|acc])
  end

  def counter(list), do: counter(list, {0, 0})
  defp counter([], {r, b}), do: {r, b}
  defp counter([:b|t], {r, b}), do: counter(t, {r, b+1})
  defp counter([:r|t], {r, b}), do: counter(t, {r+1, b})

  def add_probability(list), do: ap(list, 1, 1)
  defp ap([], _, acc), do: acc
  defp ap([:r|t], index, acc), do: ap(t, index+1, acc * index)
  defp ap([:b|t], index, acc), do: ap(t, index+1, acc)

  def factorial(n), do: fac(n, 1)
  defp fac(0, acc), do: acc
  defp fac(n, acc), do: fac(n-1, acc * n)

  @doc """
  ## Example
  
      iex> Generator.arrange([1, 2, 3])
      [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]
  """
  @spec arrange(List) :: List
  def arrange(lst), do: arg(lst) |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end) |> MapSet.to_list()
  defp arg(lst) when length(lst) == 1, do: [lst]
  defp arg([h|t]), do: arrange(t) |> Enum.reduce([], fn x, acc -> insert(h, x) ++ acc end)
  defp insert(n, lst), do: 0..length(lst) |> Enum.map(fn x -> List.insert_at(lst, x, n) end)

  def make_list(rn), do: ml(rn, 1, [])
  defp ml(_, index, acc) when index > @round, do: acc
  defp ml(rn, index, acc) when index > rn, do: ml(rn, index+1, [:b|acc])
  defp ml(rn, index, acc), do: ml(rn, index+1, [:r|acc])

  def solution() do
    wins = 0..7 |> Enum.map(fn x -> make_list(x) end)
    |> Enum.reduce([], fn x, acc -> acc ++ arrange(x) end)
    |> Enum.map(fn x -> add_probability(x) end)
    |> Enum.sum()
    all = factorial(@round+1)
    Logger.info("all: #{all}, win: #{wins}")
    div(all, wins)
  end
end
