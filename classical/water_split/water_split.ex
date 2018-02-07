defmodule WaterSplit do
  @moduledoc """
  三桶水均分8升水，求出所有的解法，三桶的容积分别为3,5,8
  解题思路：
  1. 由当前状态得到所有可能的合法动作
  2. 由合法动作得到下一个状态
  3. 建立一个状态队列来实现状态记录以及检查新状态是否在队列中已经出现，避免形成死循环
  4. 递归搜索，在达到final状态时终止
  """
  require Logger
  @doc """
  倒一次水, 所有的结果
  笨办法，一个个枚举
  """
  def pull_once(0, 0, 8), do: [[0, 5, 3], [3, 0, 5]]
  def pull_once(0, 5, 3), do: [[3, 2, 3], [3, 5, 0]]
  def pull_once(3, 0, 5), do: [[0, 3, 5], [3, 5, 0]]
  def pull_once(3, 5, 0), do: [[0, 5, 3], [3, 0, 5]]
  def pull_once(0, 3, 5), do: [[3, 0, 5], [3, 3, 2], [0, 5, 3]]
  def pull_once(0, 2, 6), do: [[2, 0, 6], [3, 2, 3], [0, 5, 3]]
  def pull_once(3, 3, 2), do: [[1, 5, 2], [0, 3, 5], [3, 0, 5], [3, 5, 0]]
  def pull_once(2, 0, 6), do: [[0, 2, 6], [3, 0, 5], [2, 5, 1]]
  def pull_once(3, 2, 3), do: [[0, 5, 3], [0, 2, 6], [3, 0, 5], [3, 5, 0]]
  def pull_once(1, 5, 2), do: [[0, 5, 3], [3, 3, 2], [1, 0, 7], [3, 5, 0]]
  def pull_once(2, 5, 1), do: [[0, 5, 3], [3, 4, 1], [3, 5, 0]]
  def pull_once(1, 0, 7), do: [[0, 1, 7], [3, 0, 5], [1, 5, 2]]
  def pull_once(3, 4, 1), do: [[2, 5, 1], [0, 4, 4], [3, 0, 5], [3, 5, 0]]
  def pull_once(0, 1, 7), do: [[1, 0, 7], [3, 1, 4], [0, 5, 3]]
  def pull_once(3, 1, 4), do: [[0, 4, 4], [0, 1, 7], [3, 0, 5], [3, 5, 0]]


  @doc """
  检查是否在链条里面，避免形成死循环
  """
  def in_queue?(queue, state), do: iq(queue, state)
  defp iq([h|_t], state) when h == state, do: true
  defp iq([_|t], state), do: iq(t, state)
  defp iq([], _state), do: false


  @doc """
  状态转换, 状态链扩展
  """
  def sl_chain([[0, 4 ,4] | _t]=queue), do: [queue]
  def sl_chain([[a, b, c] | _t]=queue) do
    next_states = pull_once(a, b, c) |> Enum.filter(fn x -> not in_queue?(queue, x) end)
    cond do
      length(next_states) == 0 -> [] # 该链断裂
      :else -> next_states |> Enum.map(fn x -> [x | queue] end)
    end
  end

  def sl_chains(queues), do: queues |> Enum.reduce([], fn x, acc -> sl_chain(x) ++ acc end)

  defp equal?(a, b), do: a == b

  @doc """
  检查是否全部完成了
  """
  defp all_finish?(queues) do
    queues |> Enum.filter(fn [x|_] -> x == [0, 4, 4] end)
    |> length() |> equal?(length(queues))
  end
  
  def solution() do
    queues = sl_chain([[0, 0, 8]])
    sl(queues)
  end

  defp sl(queues) do
    cond do
      queues |> all_finish?() -> queues
      :else -> sl_chains(queues) |> sl()
    end
  end
  
end
