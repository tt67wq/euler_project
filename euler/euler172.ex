defmodule Euler172 do
  @moduledoc """
  https://projecteuler.net/problem=172
  """
  @top 18

  require Integer

  def max_occur(0), do: 1
  def max_occur(num), do: mo(num, %{})
  defp mo(0, acc), do: Map.to_list(acc) |> Enum.map(fn {_, x} -> x end) |> Enum.max()
  defp mo(num, acc), do: mo(div(num, 10), Map.update(acc, rem(num, 10), 1, fn y -> y + 1 end))

  def pow(_, 0), do: 1
  def pow(x, n) when Integer.is_odd(n), do: x * pow(x, n - 1)

  def pow(x, n) do
    result = pow(x, div(n, 2))
    result * result
  end

  def fingerprint(num),
    do: num2digits(num) |> Enum.reduce("", fn x, acc -> acc <> Integer.to_string(x) end)

  def num2digits(0), do: [0]
  def num2digits(num), do: n2d(num, [])
  defp n2d(0, acc), do: Enum.sort(acc)
  defp n2d(num, acc), do: n2d(div(num, 10), [rem(num, 10) | acc])

  def init(), do: :ets.new(:euler172, [:named_table])

  def bfs(_num, @top), do: 1

  def bfs(num, deep) do
    fp = fingerprint(num)

    case :ets.lookup(:euler172, fp) do
      [{_, v}] ->
        v

      [] ->
        s =
          0..9
          |> Enum.map(fn x -> num * 10 + x end)
          |> Enum.filter(fn x -> max_occur(x) <= 3 end)
          |> Enum.map(fn x -> bfs(x, deep + 1) end)
          |> Enum.sum()

        :ets.insert(:euler172, {fp, s})
        s
    end
  end

  # def test() do
  #   1..(pow(10, @top) - 1)
  #   |> Enum.filter(fn x -> max_occur(x) <= 3 end)
  # end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      1..9
      |> Enum.map(fn x -> bfs(x, 1) end)
      |> Enum.sum()

    IO.inspect(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
