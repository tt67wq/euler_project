defmodule Euler61 do
  @moduledoc """
  https://projecteuler.net/problem=61
  """

  # 各种数的通项公式
  def triangle(n), do: div(n * (n + 1), 2)
  def square(n), do: n * n
  def pentagonal(n), do: div(n * (3 * n - 1), 2)
  def hexagonal(n), do: n * (2 * n - 1)
  def heptagonal(n), do: div(n * (5 * n - 3), 2)
  def octagonal(n), do: n * (3 * n - 2)

  def digit_match(n1, n2), do: rem(n1, 100) == div(n2, 100)

  defp dfs(pid, _, 0, [h | _] = acc) do
    [h1 | _] = Enum.reverse(acc)

    cond do
      digit_match(h, h1) -> send(pid, {:ok, acc})
      :else -> nil
    end
  end

  defp dfs(pid, set, deep, [h | _] = acc) do
    set
    |> Enum.map(fn x -> {x, Enum.filter(x, fn y -> digit_match(h, y) end)} end)
    |> Enum.filter(fn {_x, y} -> Enum.count(y) > 0 end)
    |> Enum.each(fn {x, y} ->
      Enum.each(y, fn z -> dfs(pid, MapSet.delete(set, x), deep - 1, [z | acc]) end)
    end)
  end

  def loop_accept() do
    receive do
      {:ok, result} ->
        IO.inspect(Enum.reverse(result))
        IO.puts(Enum.sum(result))
        loop_accept()
    end
  end

  @spec now() :: integer()
  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    ts =
      45..140
      |> Enum.map(fn x -> triangle(x) end)
      |> Enum.filter(fn x -> rem(x, 10) != 0 end)

    ss =
      32..99
      |> Enum.map(fn x -> square(x) end)
      |> Enum.filter(fn x -> rem(x, 10) != 0 end)

    ps =
      26..81
      |> Enum.map(fn x -> pentagonal(x) end)
      |> Enum.filter(fn x -> rem(x, 10) != 0 end)

    hexs =
      23..70
      |> Enum.map(fn x -> hexagonal(x) end)
      |> Enum.filter(fn x -> rem(x, 10) != 0 end)

    heps =
      21..63
      |> Enum.map(fn x -> heptagonal(x) end)
      |> Enum.filter(fn x -> rem(x, 10) != 0 end)

    os =
      19..58
      |> Enum.map(fn x -> octagonal(x) end)
      |> Enum.filter(fn x -> rem(x, 10) != 0 end)

    {:ok, pid} = Task.start(fn -> loop_accept() end)

    ts |> Enum.each(fn x -> dfs(pid, MapSet.new([ss, ps, hexs, heps, os]), 5, [x]) end)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
