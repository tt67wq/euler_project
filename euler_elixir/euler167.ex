defmodule Euler167 do
  @moduledoc """
  https://projecteuler.net/problem=167

  http://oeis.org/A100729
  http://oeis.org/A100730
  """
  require Logger

  @target 100_000_000_000
  @periods [32, 26, 444, 1628, 5906, 80, 126_960, 380_882, 2_097_152]
  @diffs [126, 126, 1778, 6510, 23622, 510, 507_842, 1_523_526, 8_388_606]

  # # 硬算序列
  # def ulam(a, b), do: ulam_iter(MapSet.new([a + b]), MapSet.new(), 0, [b, a])

  # defp ulam_iter(_, _, @top, acc), do: Enum.reverse(acc)

  # defp ulam_iter(set, jump_set, index, acc) do
  #   next = Enum.min(set)

  #   set = MapSet.delete(set, next)

  #   # 重复的加入jump_set
  #   new_jump_set =
  #     Enum.map(acc, fn x -> x + next end)
  #     |> Enum.filter(fn x -> MapSet.member?(set, x) end)
  #     |> Enum.reduce(jump_set, fn x, acc -> MapSet.put(acc, x) end)
  #     |> MapSet.to_list()
  #     |> Enum.filter(fn x -> x > next end)
  #     |> MapSet.new()

  #   new_set =
  #     Enum.map(acc, fn x -> x + next end)
  #     |> Enum.reduce(set, fn x, acc -> MapSet.put(acc, x) end)

  #   ulam_iter(MapSet.difference(new_set, new_jump_set), new_jump_set, index + 1, [next | acc])
  # end

  def ulam(a, b, top) do
    Logger.info("#{a}, #{b}, #{top}")

    port =
      Port.open({:spawn_executable, "./ulam.py"},
        args: ["#{a}", "#{b}", "#{top}"]
      )

    loop_accept(port, [])
  end

  def loop_accept(port, acc) do
    receive do
      {^port, {:data, result}} ->
        seq =
          result
          |> List.to_string()
          |> String.split(",", trim: true)
          |> Enum.map(fn x -> String.to_integer(x) end)

        # IO.inspect(Enum.reverse(seq))
        loop_accept(port, acc ++ seq)
    after
      1000 ->
        send(port, {self(), :close})
        acc
    end
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      Enum.zip([[5, 7, 9, 11, 13, 15, 17, 19, 21], @periods, @diffs])
      |> Enum.map(fn {x, y, z} -> {ulam(2, x, first_match(y, 1000)), y, z} end)
      |> Enum.map(fn {seq, y, z} -> iter(seq, 1, y, z) end)
      # |> Enum.take(9)
      |> Enum.sum()

    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end

  defp iter([h | t], index, period, diff) when index > 1000 do
    case rem(@target - index, period) do
      0 ->
        # 刚好剩余整数个循环结
        h + div(@target - index, period) * diff

      _ ->
        iter(t, index + 1, period, diff)
    end
  end

  defp iter([_h | t], index, period, diff), do: iter(t, index + 1, period, diff)

  defp first_match(period, index) do
    case rem(@target - index, period) do
      0 -> index
      _ -> first_match(period, index + 1)
    end
  end
end
