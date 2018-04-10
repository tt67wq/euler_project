defmodule SuffixTrie do
  @moduledoc """
  Documentation for SuffixTrie.
  """

  alias SuffixTrie.Node
  require Logger
  require String

  # initialize
  def step(value), do: _step(value, [])
  def _step([], acc), do: acc
  def _step([_head | tail]=value, acc), do: _step(tail, [{value, to_string(value)} | acc])

  def new(), do: %Node{}
  def new(value) do
    do_new(%Node{}, step(value))
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

  defp _insert([%Node{key: k}=head | ctail], [k | tail], value) do
    Logger.info("#{k}与#{inspect head}匹配")
    [%Node{head | children: _insert(head.children, tail, value)} | ctail]
  end

  defp _insert([h | tail], key, value) do
    [h | _insert(tail, key, value)]
  end

  defp _insert([], [], _v) do
    []
  end
  
  defp _insert([], [k], v) do
    [%Node{key: k, value: v}]
  end

  defp _insert([], [h | t], value) do
    Logger.info("无匹配项，新增child")
    [%Node{key: h, children: _insert([], t, value)}]
  end

end
