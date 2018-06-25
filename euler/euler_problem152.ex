defmodule Euler152 do
  @moduledoc """
  https://projecteuler.net/problem=152
  """
  require Logger

  def start() do
    :ets.new(:eu152, [:named_table])
  end

  def find(_n, _m, []), do: []

  def find(n, m, [h | t]) do
    case :ets.lookup(:eu152, {n, m}) do
      [{{^n, ^m}, value}] ->
        value

      [] ->
        # 没缓存
        cond do
          n * h * h - m < 0 ->
            []

          :else ->
            case n * h * h - m do
              0 ->
                :ets.insert(:eu151, {{n, m}, [[h]]})
                [[h]]

              _ ->
                v = find(n * h * h - m, m * h * h, t)

                case v do
                  [] ->
                    # 没结果
                    find(n, m, t)

                  _ ->
                    # 有结果
                    Enum.map(v, fn x -> [h | x] end)
                end
            end
        end
    end
  end

  def demo() do
    start()
    find(1, 2, 2..45 |> Enum.to_list())
  end
end
