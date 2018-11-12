defmodule Euler161 do
  @moduledoc """
  https://projecteuler.net/problem=161
  """

  @triomino1 %{0 => [1, 1], 1 => [1, 0]}
  @triomino2 %{0 => [1, 1], 1 => [0, 1]}
  @triomino3 %{0 => [1, 0], 1 => [1, 1]}
  @triomino4 %{0 => [0, 1], 1 => [1, 1]}
  @triomino5 %{0 => [1, 0], 1 => [1, 0], 2 => [1, 0]}
  @triomino6 %{0 => [1, 1, 1]}

  def now(), do: :os.system_time(:milli_seconds)

  @doc """
  状态机变换
  问题核心
  采用先填左侧，先填底部的原则避免重复
  每个阶段要过滤掉不合格的状态
  """
  def state_iter(state) do
  end

  @doc """
  状态机收集
  """
  def loop_accept(acc) do
  end

  def run() do
    {:ok, pid} = Task.start_link(fn -> loop_accept([]) end)

    init_state = %{
      8 => [0, 0],
      7 => [0, 0],
      6 => [0, 0],
      5 => [0, 0],
      4 => [0, 0],
      3 => [0, 0],
      2 => [0, 0],
      1 => [0, 0],
      0 => [0, 0]
    }

    state_iter(init_state)
  end
end
