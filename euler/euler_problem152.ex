defmodule Euler152 do
  @moduledoc """
  https://projecteuler.net/problem=152
  """
  require Logger

  def start() do
    :ets.new(:eu152, [:named_table])
  end

  def inverse_sqr_sum(_, {0, _}, acc), do: acc
  def inverse_sqr_sum([], _, _acc), do: []

  def inverse_sqr_sum([h | t], {n, m}, acc) do
    inverse_sqr_sum(t, {n * h * h - m, m * h * h}, [h | acc])
  end

  def demo() do
    inverse_sqr_sum([2, 3, 4, 5, 7, 12, 15, 20, 28, 35], {1, 2}, [])
    # find(1, 2, 2..35 |> Enum.to_list())
  end
end
