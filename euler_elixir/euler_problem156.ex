defmodule Euler156 do
  @moduledoc """
  https://projecteuler.net/problem=156
  """
  def count_digit([h | t], d) when h != d do
    count_digit(t, d) + count([h], d)
  end
end
