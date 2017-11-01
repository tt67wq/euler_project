defmodule StringPatricia do
  @moduledoc """
  Documentation for StringPatricia.
  """

  alias StringPatricia.Node
  require Logger

  def new(), do: %Node{}
  def new(values) do
    do_new(%Node{}, values)
  end

  defp do_new(tree, []), do: tree
  defp do_new(tree, [{key, value} | tail]) do
    do_new(insert(tree, key, value), tail)
  end

  def insert(nil, key, value), do: %Node{children: [%Node{key: key, value: value}]}
  def insert(%Node{key: nil, children: []}, key, value) do
    Logger.info("插入一个空树")
    %Node{children: [%Node{key: key, value: value}]}
  end

  def insert(%Node{key: nil, children: children}=tree, key, value) do
    Logger.info("插入#{key}至#{inspect tree}")
    %Node{tree | children: _insert(children, key, value)}
  end

  def insert(%Node{key: key1}=t, key2, value2) do
    Logger.info("插入#{key2}至#{inspect t}")
    %{key1: k1, key2: k2, prefix: prefix} = lcp(key1, key2)
    case prefix do
      '' -> %Node{children: [t, %Node{key: key2, value: value2}]}
      _ -> lcp_insert(prefix, k1, k2, t, value2)
    end
  end

  defp _insert([%Node{key: key} | tail], key, value) do
    [%Node{key: key, value: value} | tail]
  end

  defp _insert([%Node{key: key1}=t | tail], key2, v2) do
    %{key1: k1, key2: k2, prefix: prefix} = lcp(key1, key2)
    case prefix do
      '' -> [t | _insert(tail, key2, v2)]
      _ -> [lcp_insert(prefix, k1, k2, t, v2) | tail]
    end    
  end

  defp _insert([], k, v) do
    [%Node{key: k, value: v}]
  end


  def lcp_insert(_prefix, '', k2, t, v2) do
    %Node{t | children: [%Node{key: k2, value: v2}]}
  end

  def lcp_insert(prefix, k1, '', %Node{value: value, children: children}, v2) do
    %Node{children: [%Node{key: k1, value: value} | children], value: v2, key: prefix}
  end

  def lcp_insert(prefix, k1, k2, %Node{value: value, children: children}, v2) do
    %Node{key: prefix, children: [%Node{key: k2, value: v2} | [%Node{key: k1, value: value} | children]]}
  end

  def lcp(x, y), do: _lcp(x, y, [])
  defp _lcp([head | tail1], [head | tail2], acc), do: _lcp(tail1, tail2, [head | acc])
  defp _lcp(x, y, acc), do: %{key1: x, key2: y, prefix: Enum.reverse(acc)}

end
