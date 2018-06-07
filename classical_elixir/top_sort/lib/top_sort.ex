defmodule TopSort do
  @moduledoc """
  拓扑排序
  """
  require Logger

  alias TopSort.Queue
  # alias TopSort.Node

  def sort(graph) do
    q = Queue.new()

    iter(
      graph,
      Queue.push(q, filter_zero_in(graph)),
      []
    )
    |> Enum.reverse()
  end

  def iter(graph, q, acc) do
    len = Queue.length(q)

    case len do
      0 ->
        acc

      _ ->
        {{name, _} = node, nq} = Queue.pop(q)
        ngraph = update_graph(graph, node)

        iter(
          ngraph,
          Queue.push(nq, filter_zero_in(ngraph)),
          [name | acc]
        )
    end
  end

  @doc """
  筛选入度为0的节点
  """
  def filter_zero_in(graph) do
    zero_in? = fn {_, x} -> x.inCount == 0 end

    zs = Enum.filter(graph, zero_in?)

    cond do
      length(zs) > 0 ->
        {_, ms} = Enum.min_by(zs, fn {_, x} -> x.stime end)

        Enum.filter(zs, fn {_, x} -> x.stime == ms.stime end)
        |> Enum.sort_by(fn {_, x} -> -x.cost end)
        |> List.first()

      :else ->
        nil
    end
  end

  @doc """
  某个点出列的时候更新图
  """
  def update_graph(graph, node) do
    {name, node_obj} = node

    node_obj.adjacentNodes
    |> Enum.map(fn x -> graph[x] end)
    |> Enum.map(fn x -> Map.update!(x, :inCount, fn y -> y - 1 end) end)
    |> Enum.map(fn x ->
      Map.update!(x, :adjacentNodes, fn y -> Enum.filter(y, fn z -> z != name end) end)
    end)
    |> Enum.reduce(graph, fn x, acc -> Keyword.put(acc, x.name, x) end)
    |> Keyword.delete(name, node_obj)
  end

  def solution() do
    graph = [
      {:p1,
       %TopSort.Node{
         name: :p1,
         cost: 8,
         stime: 0,
         inCount: 0,
         adjacent: 2,
         adjacentNodes: [:p3, :p7]
       }},
      {:p2,
       %TopSort.Node{
         name: :p2,
         cost: 5,
         stime: 0,
         inCount: 0,
         adjacent: 2,
         adjacentNodes: [:p3, :p5]
       }},
      {:p3,
       %TopSort.Node{
         name: :p3,
         cost: 6,
         stime: 8,
         inCount: 2,
         adjacent: 3,
         adjacentNodes: [:p1, :p2, :p4]
       }},
      {:p4,
       %TopSort.Node{
         name: :p4,
         cost: 4,
         stime: 14,
         inCount: 1,
         adjacent: 3,
         adjacentNodes: [:p3, :p6, :p9]
       }},
      {:p5,
       %TopSort.Node{
         name: :p5,
         cost: 7,
         stime: 5,
         inCount: 1,
         adjacent: 2,
         adjacentNodes: [:p2, :p6]
       }},
      {:p6,
       %TopSort.Node{
         name: :p6,
         cost: 7,
         stime: 18,
         inCount: 2,
         adjacent: 2,
         adjacentNodes: [:p5, :p4]
       }},
      {:p7,
       %TopSort.Node{
         name: :p7,
         cost: 4,
         stime: 8,
         inCount: 1,
         adjacent: 2,
         adjacentNodes: [:p1, :p8]
       }},
      {:p8,
       %TopSort.Node{
         name: :p8,
         cost: 3,
         stime: 12,
         inCount: 1,
         adjacent: 2,
         adjacentNodes: [:p7, :p9]
       }},
      {:p9,
       %TopSort.Node{
         name: :p9,
         cost: 4,
         stime: 18,
         inCount: 2,
         adjacent: 2,
         adjacentNodes: [:p8, :p4]
       }}
    ]

    sort(graph)
  end
end
