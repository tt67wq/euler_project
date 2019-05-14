defmodule Euler199 do
  @moduledoc """
  read https://stackoverflow.com/questions/22118029/recursively-create-apollonian-gaskets-with-solution first
  """
  require Logger

  def loop_accept(acc) do
    receive do
      {:ok, r} ->
        loop_accept(acc + r)

      {:finish, pid} ->
        send(pid, {:ok, acc})
    end
  end

  defp create_ag(_c1, _c2, _c3, 6, _pid), do: nil

  defp create_ag(c1, c2, c3, index, pid) do
    cn = c1 + c2 + c3 + 2 * :math.sqrt(c1 * c2 + c1 * c3 + c2 * c3)
    send(pid, {:ok, 1 / (cn * cn)})
    create_ag(c1, c2, cn, index + 1, pid)
    create_ag(c1, c3, cn, index + 1, pid)
    create_ag(c2, c3, cn, index + 1, pid)
  end

  def create_ag(c1, c2, c3) do
    {:ok, pid} = Task.start(fn -> loop_accept(0.0) end)
    create_ag(c1, c2, c3, 1, pid)
    send(pid, {:finish, self()})

    receive do
      {:ok, acc} ->
        Process.exit(pid, :kill)
        acc
    end
  end

  def run do
    r = 2.1547005383792515
    sum = 3 * create_ag(0.4641016151377546, 1, 1) + create_ag(1, 1, 1) + 3
    1 - sum / (r * r)
  end
end
