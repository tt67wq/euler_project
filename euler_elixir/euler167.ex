defmodule Euler167 do
  @moduledoc """
  https://projecteuler.net/problem=167

  http://oeis.org/A100729
  http://oeis.org/A100730
  """
  require Logger

  @target 100_000_000_000
  @top 2000
  @periods [32, 26, 444, 1628, 5906, 80, 126_960, 380_882, 2_097_152]
  @diffs [126, 126, 1778, 6510, 23622, 510, 507_842, 1_523_526, 8_388_606]

  # 硬算序列
  def ulam(a, b), do: ulam_iter(MapSet.new([a + b]), MapSet.new(), 0, [b, a])

  defp ulam_iter(_, _, @top, acc), do: Enum.reverse(acc)

  defp ulam_iter(set, jump_set, index, acc) do
    next = Enum.min(set)

    set = MapSet.delete(set, next)

    # 重复的加入jump_set
    new_jump_set =
      Enum.map(acc, fn x -> x + next end)
      |> Enum.filter(fn x -> MapSet.member?(set, x) end)
      |> Enum.filter(fn x -> x > next end)
      |> Enum.reduce(jump_set, fn x, acc -> MapSet.put(acc, x) end)

    new_set =
      Enum.map(acc, fn x -> x + next end)
      |> Enum.reduce(set, fn x, acc -> MapSet.put(acc, x) end)

    ulam_iter(MapSet.difference(new_set, new_jump_set), new_jump_set, index + 1, [next | acc])
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      Enum.zip([[5, 7, 9, 11, 13, 15, 17, 19, 21], @periods, @diffs])
      |> Stream.map(fn {x, y, z} -> {ulam(2, x), y, z} end)
      |> Stream.map(fn {x, y, z} -> iter(x, 0, y, z) end)
      |> Enum.take(10)
      |> Enum.sum()

    IO.inspect(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end

  defp iter([h], index, period, diff), do: h + div(@target - index, period) * diff

  defp iter([h | t], index, period, diff) do
    case rem(@target - index, period) do
      0 ->
        # 刚好剩余整数个循环结
        h + div(@target - index, period) * diff

      _ ->
        iter(t, index + 1, period, diff)
    end
  end
end
