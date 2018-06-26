defmodule Euler152 do
  @moduledoc """
  https://projecteuler.net/problem=152
  """
  require Logger

  def start() do
    :ets.new(:eu152, [:named_table])
  end

  def find(n, _, _) when n < 0, do: []
  def find(0, _, _), do: [[]]
  def find(_n, _m, []), do: []

  def find(n, m, [h | t]) do
    case :ets.lookup(:eu152, {n, m}) do
      [{{^n, ^m}, vs}] ->
        vs

      [] ->
        # 缓存没命中
        # 尝试选取h，看看是否能拿到结果
        vs = find(n * h * h - m, m * h * h, t)

        res =
          case vs do
            [] ->
              # 选取h的情况下无法获得结果, 放弃h, 看后续的候选元素
              find(n, m, t)

            _ ->
              # 选择h的情况下能获得正确结果，但是依然需要看后续的选择
              Logger.info("#{n}, #{m}, #{inspect(vs)}")
              Enum.map(vs, fn x -> [h | x] end)
          end

        if res == [] do
          []
        else
          :ets.insert(:eu152, {{n, m}, res})
          res
        end
    end
  end

  def demo() do
    start()
    # find(129, 400, 2..10 |> Enum.to_list())
    find(1, 2, 2..45 |> Enum.to_list())
  end
end
