defmodule TopSort.Node do
  defstruct name: nil, # 节点名
            cost: nil, # 消耗
            stime: nil, # 起始时间
            inCount: nil, # 入度
            adjacent: nil, # 邻点数量
            adjacentNodes: nil # 邻点列表
end
