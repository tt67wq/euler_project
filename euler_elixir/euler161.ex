defmodule Euler161 do
  @moduledoc """
  https://projecteuler.net/problem=161
  """
  @triominos [
    [{0, 0}, {1, 0}, {0, 1}],
    [{0, 0}, {1, 0}, {1, 1}],
    [{0, 0}, {0, 1}, {1, 1}],
    [{0, 0}, {1, 0}, {1, -1}],
    [{0, 0}, {0, 1}, {0, 2}],
    [{0, 0}, {1, 0}, {2, 0}]
  ]

  def now(), do: :os.system_time(:milli_seconds)

  @doc """
  状态机变换
  问题核心
  采用先填左侧，先填底部的原则避免重复
  每个阶段要过滤掉不合格的状态
  """
  def state_iter(state, index) do
    # 从6种积木中选一个塞进状态机，按照先左先下的原则
  end

  @doc """
  状态机收集
  """
  def loop_accept(acc) do
  end

  def run() do
    {:ok, pid} = Task.start_link(fn -> loop_accept([]) end)

    # 初始状态
    init_state =
      for x <- 0..1,
          y <- 0..8 do
        {x, y, 0}
      end

    state_iter(init_state, 0)
  end
end
