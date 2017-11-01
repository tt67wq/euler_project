defmodule StringTrie do
  @moduledoc """
  Documentation for StringTrie.
  """

  alias StringTrie.Node
  require Logger
  
  # initialize
  def new(), do: %Node{}
  def new(values) do
    do_new(%Node{}, values)
  end

  defp do_new(tree, []), do: tree
  defp do_new(tree, [{key, value} | tail]) do
    do_new(insert(tree, key, value), tail)
  end

  def insert(%Node{key: nil, children: []}, key, value) do
    Logger.info("插入一个空树")
    %Node{children: _insert([], key, value)}
  end

  def insert(%Node{key: nil, children: children}=t, key, value) do
    Logger.info( fn -> "插入#{key}至#{inspect t}" end)
    %Node{t | children: _insert(children, key, value)}
  end

  def _insert([%Node{key: k}=head | ctail], [k | tail], value) do
    Logger.info("#{k}与#{inspect head}匹配")
    [%Node{head | children: _insert(head.children, tail, value)} | ctail]
  end

  def _insert([h | tail], key, value) do
    [h | _insert(tail, key, value)]
  end

  def _insert([], [], _v) do
    []
  end
  
  def _insert([], [k], v) do
    [%Node{key: k, value: v}]
  end

  def _insert([], [h | t], value) do
    Logger.info("无匹配项，新增child")
    [%Node{key: h, children: _insert([], t, value)}]
  end

end
