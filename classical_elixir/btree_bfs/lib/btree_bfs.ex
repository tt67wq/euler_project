defmodule BtreeBfs do
  @moduledoc """
  二叉树的层次遍历
  """

  alias BtreeBfs.Queue
  alias BtreeBfs.Tree

  def bfs(tree) do
    q = Queue.new()
    iter(q |> Queue.insert(tree), [])
  end

  defp iter(q, acc) do
    len = Queue.length(q)

    case len do
      0 ->
        acc

      _ ->
        {tree, nq} = Queue.pop(q)

        iter(nq |> Queue.insert(tree.left) |> Queue.insert(tree.right), [
          {tree.key, tree.value} | acc
        ])
    end
  end

  def generate_rand_tree(size) do
    1..size
    |> Enum.shuffle()
    |> Enum.map(fn x -> {x, x} end)
    |> Tree.new()
  end
end
