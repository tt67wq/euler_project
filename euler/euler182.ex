defmodule Euler182 do
  @moduledoc """
  https://projecteuler.net/problem=182
  """

  require Integer

  def now(), do: :os.system_time(:milli_seconds)

  def run do
    start = now()
    p = 1009
    q = 3643
    t = (p - 1) * (q - 1)

    res =
      2..(t - 1)
      |> Enum.filter(fn x -> Integer.gcd(x, t) == 1 end)
      |> Enum.map(fn x -> {x, unconcealed_num(x, p, q)} end)
      |> Enum.filter(fn {_, x} -> x == 9 end)
      |> Enum.map(fn {x, _} -> x end)
      |> Enum.sum()

    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end

  defp unconcealed_num(e, p, q) do
    (Integer.gcd(e - 1, p - 1) + 1) * (Integer.gcd(e - 1, q - 1) + 1)
  end
end
