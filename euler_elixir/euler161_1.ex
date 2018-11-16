defmodule Euler161 do
  @moduledoc """
  https://projecteuler.net/problem=161
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

  # 计算填充state共有多少种path
  def calculate_path(state) do
    w = Map.get(state, :wide)
    l = Map.get(state, :length)

    # search cache
    scode = state_encode(state, w, l)

    case :ets.lookup(:euler161, scode) do
      [{^scode, value}] ->
        value

      [] ->
        # miss
        {flag, a, b} = position_find(state, w, l, 0, 0)

        case flag do
          :error ->
            1

          :ok ->
            # 塞入积木
            v =
              @triominos
              |> Enum.map(fn tr -> add_triominos(state, w, l, {a, b}, tr) end)
              |> Enum.filter(fn {flag, _} -> flag == :ok end)
              |> Enum.map(fn {_, nst} -> calculate_path(nst) end)
              |> Enum.sum()

            # add to cache
            :ets.insert(:euler161, {scode, v})
            v
        end
    end
  end

  defp state_encode(state, w, l) do
    for x <- 0..w,
        y <- 0..l do
      {x, y}
    end
    |> Enum.map(fn pos -> Map.get(state, pos) end)
    |> Enum.join()
  end

  def run() do
    start = now()

    :ets.new(:euler161, [:named_table])

    wide = 11
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
