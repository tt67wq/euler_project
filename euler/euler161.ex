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

  def now(), do: :os.system_time(:milli_seconds)

  @doc """
  状态机变换
  问题核心
  采用从下至上，从左至右的原则填错避免重复
  每个阶段要过滤掉不合格的状态
  """
  def state_iter(state, pid) do
    w = Map.get(state, :wide)
    l = Map.get(state, :length)

    {flag, a, b} = position_find(state, w, l, 0, 0)

    case flag do
      :error ->
        send(pid, {:ok, 1})

      :ok ->
        # 塞入积木
        @triominos
        |> Enum.map(fn tr -> add_triominos(state, w, l, {a, b}, tr) end)
        |> Enum.filter(fn {flag, _} -> flag == :ok end)
        |> Enum.each(fn {_, nst} -> state_iter(nst, pid) end)
    end
  end

  defp position_find(_state, w, _l, a, _b) when a > w, do: {:error, 0, 0}
  defp position_find(state, w, l, a, b) when b > l, do: position_find(state, w, l, a + 1, 0)

  defp position_find(state, w, l, a, b) do
    case Map.get(state, {a, b}, -1) do
      0 -> {:ok, a, b}
      1 -> position_find(state, w, l, a, b + 1)
    end
  end

  # 在{a,b}点中塞入积木
  defp add_triominos(state, w, l, {a, b}, [{x0, y0}, {x1, y1}, {x2, y2}]) do
    # 三个点都必须在框内
    dots = [{a + x0, b + y0}, {a + x1, b + y1}, {a + x2, b + y2}]

    c =
      dots
      |> Enum.filter(fn {x, _y} -> x <= w and x >= 0 end)
      |> Enum.filter(fn {_x, y} -> y <= l and y >= 0 end)
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
      {:ok, n} ->
        loop_accept(acc + n)

      {:finish, pid} ->
        send(pid, {:ok, acc})

      {:error} ->
        loop_accept(acc)
    end
  end

  def calculate_path(state) do
    {:ok, pid} = Task.start_link(fn -> loop_accept(0) end)

    state_iter(state, pid)
    send(pid, {:finish, self()})

    receive do
      {:ok, res} ->
        res
    end
  end

  def run() do
    start = now()
    wide = 4
    length = 8

    # 初始状态
    state =
      for x <- 0..wide,
          y <- 0..length do
        {x, y}
      end
      |> Enum.reduce(%{}, fn {x, y}, acc -> Map.put(acc, {x, y}, 0) end)

    res =
      state
      |> Map.put(:wide, wide)
      |> Map.put(:length, length)
      |> calculate_path()

    IO.puts(res)
    timeuse = now() - start
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
