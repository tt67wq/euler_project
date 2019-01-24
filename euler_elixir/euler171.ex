defmodule Euler171 do
  @moduledoc """
  https://projecteuler.net/problem=171
  """
  require Integer

  defp square(n), do: n * n

  defp perfect_square?(n), do: square(round(:math.sqrt(n))) == n

  def pow(_, 0), do: 1
  def pow(x, n) when Integer.is_odd(n), do: x * pow(x, n - 1)

  def pow(x, n) do
    result = pow(x, div(n, 2))
    result * result
  end

  # search ==> {sum([x for f(x) == s and len(x)==n]), count}
  # search(n, s) = Σsearch(n-1, s-k) (k in 0..9)

  def search(_, s) when s < 0, do: {0, 0}

  def search(1, s) do
    case s do
      0 -> {0, 1}
      1 -> {1, 1}
      4 -> {2, 1}
      9 -> {3, 1}
      16 -> {4, 1}
      25 -> {5, 1}
      36 -> {6, 1}
      49 -> {7, 1}
      64 -> {8, 1}
      81 -> {9, 1}
      _ -> {0, 0}
    end
  end

  def search(n, s) do
    case :ets.lookup(:euler171, {n, s}) do
      [{_, v}] ->
        v

      [] ->
        v =
          0..9
          |> Enum.map(fn x -> {x, search(n - 1, s - x * x)} end)
          |> Enum.reduce({0, 0}, fn {x, {sum, count}}, {a, b} ->
            {a + sum + count * pow(10, n - 1) * x, b + count}
          end)

        :ets.insert(:euler171, {{n, s}, v})
        v
    end
  end

  def init() do
    :ets.new(:euler171, [:named_table])
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    top = 81 * 20

    res =
      0..top
      |> Enum.filter(fn x -> perfect_square?(x) end)
      |> Enum.map(fn x -> search(20, x) end)
      |> Enum.map(fn {x, _} -> x end)
      |> Enum.sum()
      |> rem(1_000_000_000)

    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
