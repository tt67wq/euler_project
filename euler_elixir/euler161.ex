defmodule Euler161 do
  @moduledoc """
  https://projecteuler.net/problem=161

  https://oeis.org/A215826
  """
  require Logger

  @triominos [
    [{0, 0}, {1, 0}, {0, 1}],
    [{0, 0}, {1, 0}, {1, 1}],
    [{0, 0}, {0, 1}, {1, 1}],
    [{0, 0}, {1, 0}, {1, -1}],
    [{0, 0}, {0, 1}, {-1, 1}],
    [{0, 0}, {0, 1}, {0, 2}],
    [{0, 0}, {1, 0}, {2, 0}]
  ]

  @xlimit 3
  @ylimit 8
  @ilimit 12

  def now(), do: :os.system_time(:milli_seconds)

  @doc """
  状态机变换
  问题核心
  采用先填左侧，先填底部的原则避免重复
  每个阶段要过滤掉不合格的状态
  """
  def state_iter(_state, index, pid) when index > @ilimit, do: send(pid, {:ok})

  def state_iter(state, index, pid) do
    # 从左下开始查找
    {flag, a, b} = position_find(state, 0, 0)

    case flag do
      :error ->
        # finish
        send(pid, {:ok})

      :ok ->
        # 塞入积木
        @triominos
        |> Enum.map(fn tr -> add_triominos(state, {a, b}, tr) end)
        |> Enum.filter(fn {flag, _} -> flag == :ok end)
        |> Enum.each(fn {_, nst} -> state_iter(nst, index + 1, pid) end)
    end
  end

  defp position_find(_state, _a, b) when b > @ylimit, do: {:error, 0, 0}
  defp position_find(state, a, b) when a > @xlimit, do: position_find(state, 0, b + 1)

  defp position_find(state, a, b) do
    case Map.get(state, {a, b}, -1) do
      0 -> {:ok, a, b}
      1 -> position_find(state, a + 1, b)
    end
  end

  # 在{a,b}点中塞入积木
  defp add_triominos(state, {a, b}, [{x0, y0}, {x1, y1}, {x2, y2}]) do
    # 三个点都必须在框内
    dots = [{a + x0, b + y0}, {a + x1, b + y1}, {a + x2, b + y2}]

    c =
      dots
      |> Enum.filter(fn {x, _y} -> x <= @xlimit and x >= 0 end)
      |> Enum.filter(fn {_x, y} -> y <= @ylimit and y >= 0 end)
      |> Enum.count()

    case c do
      3 ->
        # 三个点都不能为1
        vs = dots |> Enum.map(fn {x, y} -> Map.get(state, {x, y}) end)

        case vs do
          # 可填充
          [0, 0, 0] ->
            {:ok, dots |> Enum.reduce(state, fn {x, y}, acc -> Map.put(acc, {x, y}, 1) end)}

          # 冲突
          _ ->
            {:error, state}
        end

      _ ->
        {:error, state}
    end
  end

  @doc """
  状态机收集
  """
  def loop_accept(acc) do
    receive do
      {:ok} ->
        loop_accept(acc + 1)

      {:finish} ->
        IO.puts(acc)

      {:error} ->
        loop_accept(acc)
    end
  end

  def run() do
    start = now()
    {:ok, pid} = Task.start_link(fn -> loop_accept(0) end)

    # 初始状态
    init_state =
      for x <- 0..@xlimit,
          y <- 0..@ylimit do
        {x, y}
      end
      |> Enum.reduce(%{}, fn {x, y}, acc -> Map.put(acc, {x, y}, 0) end)

    state_iter(init_state, 0, pid)
    send(pid, {:finish})
    timeuse = now() - start
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
