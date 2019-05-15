defmodule Euler199 do
  @moduledoc """
  read https://stackoverflow.com/questions/22118029/recursively-create-apollonian-gaskets-with-solution first
  """
  require Logger

  defp add(a, b), do: a + b

  def create_ag(_c1, _c2, _c3, 5), do: 0

  def create_ag(c1, c2, c3, index) do
    cn = c1 + c2 + c3 + 2 * :math.sqrt(c1 * c2 + c1 * c3 + c2 * c3)

    (1 / (cn * cn))
    |> add(create_ag(c1, c2, cn, index + 1))
    |> add(create_ag(c1, c3, cn, index + 1))
    |> add(create_ag(c2, c3, cn, index + 1))
  end

  defp create_ag_out(_c1, _c2, _c3, _c4, 5), do: 0

  defp create_ag_out(c1, c2, c3, c4, index) do
    cn = 2 * (c1 + c2 + c3) - c4

    (1 / (cn * cn))
    |> add(create_ag(c2, c3, cn, index + 1))
    |> add(create_ag_out(c1, c2, cn, c3, index + 1))
    |> add(create_ag_out(c1, c3, cn, c2, index + 1))
  end

  def run do
    r = 2.1547005383792515
    sum = create_ag(1, 1, 1, 0) + 3 * create_ag_out(0.4641016151377546, 1, 1, 1, 0) + 3
    1 - sum / (r * r)
  end
end
