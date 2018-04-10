defmodule BtreeBfs.Tree do
  @moduledoc """
  简单的二叉树
  """
  defstruct key: nil, value: nil, left: nil, right: nil
  alias BtreeBfs.Tree

  def new(), do: %Tree{}
  def new([]), do: %Tree{}
  def new(data), do: data |> Enum.reduce(%Tree{}, fn {k, v}, acc -> insert(acc, {k, v}) end)

  def insert(nil, {key, value}), do: %Tree{key: key, value: value}

  def insert(tree, {key, value}) do
    cond do
      tree.key == nil ->
        %Tree{tree | key: key, value: value}

      key < tree.key ->
        %Tree{tree | left: insert(tree.left, {key, value})}

      key > tree.key ->
        %Tree{tree | right: insert(tree.right, {key, value})}

      :else ->
        tree
    end
  end
end
