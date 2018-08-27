defmodule Euler156 do
  @moduledoc """
  https://projecteuler.net/problem=156
  """
  def digit_count(10, 1), do: 2
  def digit_count(10, _), do: 1

  def digit_count(100, 1), do: 21
  def digit_count(100, _), do: 20

  def digit_count(1000, 1), do: 301
  def digit_count(1000, _), do: 300

  def digit_count(10000, 1), do: 4001
  def digit_count(10000, _), do: 4000

  def digit_count(100_000, 1), do: 50001
  def digit_count(100_000, _), do: 50000

  def digit_count(1_000_000, 1), do: 600_001
  def digit_count(1_000_000, _), do: 600_000

  def digit_count(10_000_000, 1), do: 7_000_001
  def digit_count(10_000_000, _), do: 7_000_000

  def digit_count(100_000_000, 1), do: 80_000_001
  def digit_count(100_000_000, _), do: 80_000_000

  def digit_count(1_000_000_000, 1), do: 900_000_001
  def digit_count(1_000_000_000, _), do: 900_000_000

  def digit_count(10_000_000_000, 1), do: 10_000_000_001
  def digit_count(10_000_000_000, _), do: 10_000_000_000
end
