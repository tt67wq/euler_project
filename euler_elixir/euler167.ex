defmodule Euler167 do
  @moduledoc """
  https://projecteuler.net/problem=167

  http://oeis.org/A100729
  http://oeis.org/A100730
  """
  require Logger

  @top 10000
  @prefix_limit 20
  @periodic_limit 500

  # 硬算序列
  # def ulam(a, b), do: ulam_iter(MapSet.new([a + b]), MapSet.new(), 0, [b, a])

  # defp ulam_iter(_, _, @top, acc), do: Enum.reverse(acc)

  # defp ulam_iter(set, jump_set, index, acc) do
  #   next = Enum.min(set)

  #   set = MapSet.delete(set, next)

  #   # 重复的加入jump_set
  #   new_jump_set =
  #     Enum.map(acc, fn x -> x + next end)
  #     |> Enum.filter(fn x -> MapSet.member?(set, x) end)
  #     |> Enum.filter(fn x -> x > next end)
  #     |> Enum.reduce(jump_set, fn x, acc -> MapSet.put(acc, x) end)

  #   new_set =
  #     Enum.map(acc, fn x -> x + next end)
  #     |> Enum.reduce(set, fn x, acc -> MapSet.put(acc, x) end)

  #   ulam_iter(MapSet.difference(new_set, new_jump_set), new_jump_set, index + 1, [next | acc])
  # end

  def ulam(a, b), do: ulam_iter(%{(a + b) => 1}, [b, a], 1)

  defp ulam_iter(_, acc, @top), do: Enum.reverse(acc)

  defp ulam_iter(mp, [h | _] = acc, index) do
    # {next, 1} =
    #   Map.to_list(mp)
    #   |> Enum.filter(fn {_, x} -> x == 1 end)
    #   |> Enum.min()
    {new_mp, next} = search_next(mp, h)

    # new_mp =
    #   Map.keys(mp)
    #   |> Enum.filter(fn x -> x <= next end)
    #   |> Enum.reduce(mp, fn x, bcc -> Map.delete(bcc, x) end)

    Enum.map(acc, fn x -> x + next end)
    |> Enum.reduce(new_mp, fn x, bcc -> Map.update(bcc, x, 1, &(&1 + 1)) end)
    |> ulam_iter([next | acc], index + 1)
  end

  def search_next(mp, from) do
    case Map.get(mp, from) do
      nil -> search_next(mp, from + 1)
      1 -> {Map.delete(mp, from), from}
      _ -> search_next(Map.delete(mp, from), from + 1)
    end
  end

  # 计算序列差值
  def consecutive_diff(list), do: cons_diff(list, [])
  defp cons_diff([_], acc), do: acc
  defp cons_diff([h1, h2 | t], acc), do: cons_diff([h2 | t], [h2 - h1 | acc])

  # 寻找周期串 返回前缀部分 和 周期串
  def search_periodic_part([_h | t] = list) do
    case search(t, 1) do
      {pl, periodic} ->
        {Enum.take(list, pl), Enum.count(periodic), Enum.sum(periodic)}

      _ ->
        nil
    end
  end

  defp search(_, @prefix_limit), do: nil

  defp search([_h | t] = list, prefix_len) do
    case sp(list, 10) do
      nil -> search(t, prefix_len + 1)
      {:ok, p} -> {prefix_len, p}
    end
  end

  defp sp(_list, @periodic_limit), do: nil

  defp sp(list, periodic_len) do
    ps =
      Enum.take(list, 5 * periodic_len)
      |> Enum.chunk_every(periodic_len)

    cond do
      all_equal?(ps) -> {:ok, List.first(ps)}
      :else -> sp(list, periodic_len + 1)
    end
  end

  def all_equal?([h | t]) do
    case Enum.find(t, fn x -> x != h end) do
      nil -> true
      _ -> false
    end
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    res = ulam(2, 5)
    IO.inspect(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
