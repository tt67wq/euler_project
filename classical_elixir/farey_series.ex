defmodule FareySeries do
  @moduledoc """
  生成分母不大于N的Farey序列
  """
  require Logger

  def gcd(a, 0), do: a
  def gcd(a, b), do: gcd(b, rem(a, b))

  defp build(n, a, b, x, y, res) do
    g = gcd(a + x, b + y)
    p = div(a + x, g)
    q = div(b + y, g)

    if q <= n do
      build(n, p, q, x, y, [{p, q} | build(n, a, b, p, q, res)])
    else
      res
    end
  end

  def run(n) do
    res = [{0, 1}, {1, 1}]

    build(n, 0, 1, 1, 1, res)
    |> Enum.sort(fn {p1, q1}, {p2, q2} -> p1 * q2 < p2 * q1 end)
    # |> Enum.each(fn x -> Logger.info("#{inspect(x)}") end)
  end
end
