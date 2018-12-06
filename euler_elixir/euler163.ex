defmodule Euler163 do
  @moduledoc """
  https://projecteuler.net/problem=163
  """
  @size 2

  @tr :math.sqrt(3)
  @br 1 / @tr

  # 获得直线方程
  def get_lines(angle) do
    angle

    case angle do
      0 ->
        1..@size |> Enum.map(fn x -> {0, @tr * (x - 1)} end)

      30 ->
        nil
    end
  end

  def run() do
    @tr
  end
end
