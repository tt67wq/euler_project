defmodule Euler151 do
  @moduledoc """
  https://projecteuler.net/problem=151
  """
  require Logger
  # @limit 1_000_000

  def start() do
    # %{0 => 1, 1 => 0, 2 => 0, 3 => 0, 4 => 0}
    :ets.new(:eu151, [:named_table])
  end

  def batch(0, _state), do: 0

  def batch(dep, state) do
    Logger.info("aaaaaa: #{dep}, #{inspect(state)}")

    case :ets.lookup(:eu151, state) do
      [{^state, value}] ->
        Logger.info(value)
        value

      [] ->
        v = bat(dep, state)
        :ets.insert(:eu151, {state, v})
        v
    end
  end

  defp bat(dep, state) do
    tot = Enum.sum(Map.values(state))

    ans =
      case tot do
        1 -> 1
        _ -> 0
      end

    0..4
    |> Enum.filter(fn x -> Map.fetch!(state, x) != 0 end)
    |> Enum.map(fn x -> {x, state_update(state, x)} end)
    |> Enum.reduce(ans, fn {at, nst}, acc ->
      {_, v} = Enum.at(state, at)
      batch(dep - 1, nst) * v / tot + acc
    end)
  end

  def state_update(state, at) do
    decr = fn x -> x - 1 end
    incr = fn x -> x + 1 end

    if at == 4 do
      Map.update(state, 4, 0, decr)
    else
      (at + 1)..4
      |> Enum.reduce(Map.update(state, at, 0, decr), fn x, acc -> Map.update(acc, x, 0, incr) end)
    end
  end

  def solution() do
    t1 = timestamp()
    start()
    result = batch(16, %{0 => 1, 1 => 0, 2 => 0, 3 => 0, 4 => 0})
    Logger.info("result: #{result}, timeuse: #{timestamp() - t1} ms")
  end

  def timestamp(), do: :os.system_time(:micro_seconds)
end
