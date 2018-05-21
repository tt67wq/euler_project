defmodule Euler144 do
  @moduledoc """
  https://projecteuler.net/problem=144
  """
  require Logger

  @doc """
  椭圆4x*x+y*y=100在点(x0,y0)处的切线
  """
  def tangent_line({x0, y0}) do
    k = -4 * x0 / y0
    b = 100 / y0
    {k, b}
  end

  @doc """
  点(x0, y0)关于线y = kx + b的对称点
  ## Example
  iex> AnalyticGeometry.symmetry({1, 2}, 1, 0)
  {2.0, 1.0}
  """
  def symmetry({x0, y0}, k, b) do
    x1 = ((k * k - 1) * x0 + 2 * k * b - 2 * k * y0) / (-k * k - 1)
    y1 = (2 * k * k * x0 + 2 * k * (b - y0)) / ((k * k + 1) * k) + y0
    {x1, y1}
  end

  @doc """
  激光发射迭代
  ## Example

  iex> 

  """
  def iter({x0, y0}, {x1, y1}) do
    {k, b} = tangent_line({x1, y1})
    Logger.info("在点(#{x1}, #{y1})处切线方程为y = #{k}*x+#{b}")
    {x2, y2} = symmetry({x0, y0}, k, b)
    Logger.info("点(#{x0}, #{y0})关于方程y=#{k}*x+#{b}的对称点为(#{x2}, #{y2}))")
    Logger.info("连接点(#{x2},#{y2})和点(#{x1}, #{y1})")
    nk = (y2 - y1) / (x2 - x1)
    nb = y2 - x2 * (y2 - y1) / (x2 - x1)
    Logger.info("反射激光的方程为 y(x) = #{nk}*x + #{nb}")

    root = nk * nk * nb * nb / ((4 + nk * nk) * (4 + nk * nk)) - (nb * nb - 100) / (4 + nk * nk)

    x21 = :math.sqrt(root) - nb * nk / (4 + nk * nk)

    x22 = -:math.sqrt(root) - nb * nk / (4 + nk * nk)

    {x3, y3} =
      cond do
        abs(x21 - x1) > abs(x22 - x1) -> {x21, x21 * nk + nb}
        :else -> {x22, x22 * nk + nb}
      end

    {{x1, y1}, {x3, y3}}
  end

  def solution() do
    sl({0.0, 10.1}, {1.4, -9.6}, 1)
  end

  defp sl({x0, y0}, {x1, y1}, index) do
    {_, {x2, y2}} = iter({x0, y0}, {x1, y1})
    Logger.info("激光发射击中了点 (#{x2}, #{y2})")

    cond do
      x2 > -0.01 and x2 < 0.01 and y2 > 0 -> index
      :else -> sl({x1, y1}, {x2, y2}, index + 1)
    end
  end
end
