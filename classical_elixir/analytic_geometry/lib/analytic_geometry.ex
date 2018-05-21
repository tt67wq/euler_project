defmodule AnalyticGeometry do
  @moduledoc """
  解析几何中的一些工具
  """

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
end
