defmodule Euler208 do
  @moduledoc """
  路径闭合的必要条件
  """
  require Logger
  @cs 14
  @target %{0 => @cs, 1 => @cs, 2 => @cs, 3 => @cs, 4 => @cs}
  @all @cs * 5

  defp dfs(_state, acc, [4 | _], @all) do
    case acc do
      @target -> 1
      _ -> 0
    end
  end

  defp dfs(_state, _acc, _bcc, @all), do: 0

  defp dfs(state, acc, bcc, index) do
    fp = finger_print(state, acc)

    case :ets.lookup(:euler208, fp) do
      [{_, v}] ->
        v

      [] ->
        nacc = Map.update(acc, state, 1, &(&1 + 1))
        a = dfs(rem(state + 1, 5), nacc, [state | bcc], index + 1)
        b = dfs(rem(state + 4, 5), nacc, [state | bcc], index + 1)
        v = a + b
        :ets.insert(:euler208, {fp, v})
        v
    end
  end

  defp finger_print(state, acc) do
    tmp =
      [0, 1, 2, 3, 4]
      |> Enum.map(fn x -> Map.get(acc, x, 0) end)
      |> Enum.join(",")

    "#{state}:#{tmp}"
  end

  def init, do: :ets.new(:euler208, [:named_table])

  def run do
    dfs(0, %{}, [], 0)
  end
end
