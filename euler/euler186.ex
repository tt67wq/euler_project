defmodule Euler186 do
  @moduledoc """
  效率太低
  """
  # 2325629

  require Logger

  def init_ets do
    :ets.new(:euler, [:named_table])
    :ets.new(:disjoin_set, [:named_table])
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

  ####### disjoin set
  def find(x) do
    case :ets.lookup(:disjoin_set, x) do
      [{_, {^x, num}}] ->
        # root
        {x, num}

      [{_, {v, _}}] ->
        # not root
        {root, num} = find(v)

        if root != v do
          # zip
          :ets.insert(:disjoin_set, {x, {root, num}})
        end

        {root, num}

      [] ->
        # not in set
        # add new one
        :ets.insert(:disjoin_set, {x, {x, 1}})
        {x, 1}
    end
  end

  def join(x, y) do
    {xroot, xnum} = find(x)
    {yroot, ynum} = find(y)

    if xroot != yroot do
      :ets.insert(:disjoin_set, {xroot, {yroot, xnum + ynum}})
      :ets.insert(:disjoin_set, {yroot, {yroot, xnum + ynum}})
    end

    :ok
  end

  def caller(n), do: lagged_fib_generator(2 * n - 1)
  def called(n), do: lagged_fib_generator(2 * n)

  defp iter(_, suc_time, {_, chain_size}) when chain_size >= 990_000, do: suc_time

  defp iter(index, suc_time, _) do
    m = caller(index)
    n = called(index)

    cond do
      m == n ->
        iter(index + 1, suc_time, find(524_287))

      :else ->
        join(m, n)
        iter(index + 1, suc_time + 1, find(524_287))
    end
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run do
    start = now()
    res = iter(1, 0, {0, 0})
    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
