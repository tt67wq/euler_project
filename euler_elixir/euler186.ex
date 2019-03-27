defmodule Euler186 do
  @moduledoc false
  # 2325629

  require Logger

  def init_ets do
    :ets.new(:euler, [:named_table])
  end

  def lagged_fib_generator(n) do
    case :ets.lookup(:euler, n) do
      [{_, v}] ->
        v

      [] ->
        v =
          cond do
            n >= 1 and n <= 55 ->
              rem(100_003 - 200_003 * n + 300_007 * n * n * n, 1_000_000)

            :else ->
              rem(lagged_fib_generator(n - 24) + lagged_fib_generator(n - 55), 1_000_000)
          end

        :ets.insert(:euler, {n, v})
        v
    end
  end

  def caller(n), do: lagged_fib_generator(2 * n - 1)
  def called(n), do: lagged_fib_generator(2 * n)

  defp pm_size(pools) do
    v = Enum.find(pools, fn x -> MapSet.member?(x, 524_287) end)

    case v do
      nil -> 0
      _ -> MapSet.size(v)
    end
  end

  defp iter(index, suc_time, pools) do
    m = caller(index)
    n = called(index)

    p = pm_size(pools)

    cond do
      p >= 990_000 ->
        index

      m == n ->
        Logger.debug("#{index}, #{suc_time}, #{p}")
        iter(index + 1, suc_time, pools)

      :else ->
        c1 = Enum.find(pools, fn x -> MapSet.member?(x, m) end)
        c2 = Enum.find(pools, fn x -> MapSet.member?(x, n) end)

        case {c1, c2} do
          {nil, nil} ->
            # add new chain
            iter(index + 1, suc_time + 1, MapSet.put(pools, MapSet.new([m, n])))

          {nil, _} ->
            # c2 exists
            npool =
              MapSet.delete(pools, c2)
              |> MapSet.put(MapSet.put(c2, m))

            iter(index + 1, suc_time + 1, npool)

          {_, nil} ->
            # c1 exists
            npool =
              MapSet.delete(pools, c1)
              |> MapSet.put(MapSet.put(c1, m))

            iter(index + 1, suc_time + 1, npool)

          _ ->
            # both exists join 2 pool
            npool =
              MapSet.delete(pools, c1)
              |> MapSet.delete(c2)
              |> MapSet.put(MapSet.union(c1, c2))

            iter(index + 1, suc_time + 1, npool)
        end
    end
  end

  def test do
    iter(1, 0, MapSet.new())
  end
end
