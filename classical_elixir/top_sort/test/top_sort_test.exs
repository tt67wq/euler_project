defmodule TopSortTest do
  use ExUnit.Case
  doctest TopSort

  # defstruct name: nil, # 节点名
  #           cost: nil, # 消耗
  #           stime: nil, # 起始时间
  #           inCount: nil, # 入度
  #           adjacent: nil, # 邻点数量
  #           adjacentNodes: nil # 邻点列表

  test "top sort ignore cost and stime" do
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
    sorted_list = TopSort.sort(graph)
    expected = [:p1, :p2, :p5, :p3, :p7, :p8, :p4, :p6, :p9]
    assert sorted_list == expected
  end
end
