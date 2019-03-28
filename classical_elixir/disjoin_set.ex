defmodule DisjoinSet do
  @moduledoc """
  简单并查集实现
  """
  def init_set do
    :ets.new(:disjoin_set, [:named_table])
  end

  def find(x) do
    case :ets.lookup(:disjoin_set, x) do
      [{_, ^x}] ->
        # root
        x

      [{_, v}] ->
        # not root
        root = find(v)

        if root != v do
          :ets.insert(:disjoin_set, {x, root})
        end

        root

      [] ->
        # not in set
        # add new one
        :ets.insert(:disjoin_set, {x, x})
        x
    end
  end

  def join(x, y) do
    xroot = find(x)
    yroot = find(y)

    if xroot != yroot do
      :ets.insert(:disjoin_set, {xroot, yroot})
    end

    :ok
  end
end
