defmodule Euler178 do
  @moduledoc """
  https://projecteuler.net/problem=178
  """

  require Logger

  def init, do: :ets.new(:euler178, [:named_table])

  defp search(_v, 0, absent) do
    # Logger.info("#{v}, 0, #{inspect(absent)}")
    case MapSet.size(absent) do
      0 -> 1
      _ -> 0
    end
  end

  defp search(0, deep, absent) do
    # Logger.info("0, #{deep}, #{inspect(absent)}")
    case :ets.lookup(:euler178, {0, deep, absent}) do
      [{_, r}] ->
        r

      [] ->
        r = search(1, deep - 1, MapSet.delete(absent, 1))
        :ets.insert(:euler178, {{0, deep, absent}, r})
        r
    end
  end

  defp search(9, deep, absent) do
    # Logger.info("9, #{deep}, #{inspect(absent)}")
    case :ets.lookup(:euler178, {9, deep, absent}) do
      [{_, r}] ->
        r

      [] ->
        r = search(8, deep - 1, MapSet.delete(absent, 8))
        :ets.insert(:euler178, {{9, deep, absent}, r})
        r
    end
  end

  defp search(v, deep, absent) do
    # Logger.info("#{v}, #{deep}, #{inspect(absent)}")
    case :ets.lookup(:euler178, {v, deep, absent}) do
      [{_, r}] ->
        r

      [] ->
        r =
          search(v + 1, deep - 1, MapSet.delete(absent, v + 1)) +
            search(v - 1, deep - 1, MapSet.delete(absent, v - 1))

        :ets.insert(:euler178, {{v, deep, absent}, r})
        r
    end
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run do
    start = now()
    all = MapSet.new([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])

    result =
      39..9
      |> Enum.map(fn x ->
        1..9
        |> Enum.map(fn y -> search(y, x, MapSet.delete(all, y)) end)
        |> Enum.sum()
      end)
      |> Enum.sum()

    IO.puts(result)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
