defmodule Patricia do
  @moduledoc """
  Documentation for Patricia.
  """
  use Bitwise
  import Patricia.Helper
  
  alias Patricia.Node

  def new(), do: %Node{}
  def new(values) do
    do_new(%Node{}, values)
  end

  defp do_new(tree, []), do: tree
  defp do_new(tree, [{key, value} | tail]) do
    do_new(insert(tree, key, value), tail)
  end

  # insert an element into tree
  def insert(nil, key, value) do
    # insert(%Node{}, key, value)
    %Node{key: key, value: value}
  end

  def insert(%Node{key: nil, prefix: nil}, key, value) do
    %Node{key: key, value: value}
  end

  def insert(%Node{left: nil, right: nil, key: key}=tree, key, value) do
    %Node{tree | value: value}
  end

  def insert(%Node{left: nil, right: nil}=tree, key, value) do
    branch(tree, %Node{key: key, value: value})
  end
  
  def insert(%Node{
        mask: mask, prefix: prefix,
        left: nil, right: nil}=tree, key, value) when match(key, mask, prefix) and zero(key, mask) do
    x = get_prefix(value, tree.value)
    %Node{prefix: x, mask: mask(x), left: %Node{key: key, value: value}, right: tree}
  end
  
  def insert(%Node{left: nil, right: nil, mask: mask, prefix: prefix}=tree, key, value) when match(key, mask, prefix) do
    x = get_prefix(value, tree.value)
    %Node{prefix: x, mask: mask(x), right: %Node{key: key, value: value}, left: tree}
  end

  def insert(%Node{mask: mask}=tree, key, value) when zero(key, mask) do
    %Node{tree | left: insert(tree.left, key, value)}
  end

  def insert(tree, key, value) do
    %Node{tree | right: insert(tree.right, key, value)}
  end

  def lookup(nil, _key), do: nil

  def lookup(%Node{left: nil, right: nil, key: key, value: value}, key) do
    value
  end

  def lookup(%Node{left: nil, right: nil}, _key) do
    nil
  end
  
  def lookup(%Node{prefix: prefix, mask: mask}=tree, key) when match(key, mask, prefix) and zero(key, mask) do
    lookup(tree.left, key)
  end

  def lookup(%Node{prefix: prefix, mask: mask}=tree, key) when match(key, mask, prefix) do
    lookup(tree.right, key)
  end

  def lookup(_tree, _key) do
    nil
  end


  defp lcp(p1, p2), do: do_lcp(p1, p1 ^^^ p2, 1)
  defp do_lcp(p1, 0, mask), do: {maskbit(p1, mask), mask}
  defp do_lcp(p1, diff, mask), do: do_lcp(p1, diff >>> 1, mask <<< 1)

  defp branch(t1, t2) do
    {prefix, mask} = lcp(get_prefix(t1), get_prefix(t2))
    do_branch(%Node{prefix: prefix, mask: mask}, t1, t2)
  end

  defp do_branch(%Node{mask: mask}=tree, %Node{prefix: nil, key: key}=t1, t2) when zero(key, mask) do
    %Node{tree | left: t1, right: t2}
  end

  defp do_branch(%Node{mask: mask}=tree, %Node{prefix: prefix}=t1, t2) when zero(prefix, mask) do
    %Node{tree | left: t1, right: t2}
  end

  defp do_branch(tree, t1, t2), do: %Node{tree | left: t2, right: t1}

  defp get_prefix(%Node{prefix: nil}=node), do: node.key
  defp get_prefix(node), do: node.prefix

  defp get_prefix(x, y), do: x &&& y
  defp maskbit(x, y), do: get_prefix(x, bnot(y-1))

  defp mask(x), do: bnot(x) + 1

end
