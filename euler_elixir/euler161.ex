defmodule Euler161 do
  @moduledoc """
  https://projecteuler.net/problem=161
  """

  def now(), do: :os.system_time(:milli_seconds)

  @doc """
    状态机变换
  """
  def state_iter() do
  end

  @doc """
  状态机收集
  """
  def loop_accept(acc) do
  end

  def run() do
    {:ok, pid} = Task.start_link(fn -> loop_accept([]) end)
  end
end
