defmodule Euler176 do
  @moduledoc """
  https://projecteuler.net/problem=176
  47547
  """

  require Integer
  require Logger

  @ps [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71]
  @target 47547

  def count_list(list) do
    a = count_a(list)
    b = count_b(list)
    # Logger.info("#{a}, #{b}")
    a + b
  end

  ### r = 2kmn 形式
  defp count_a([h]), do: h - 1
  defp count_a([h | t]), do: (2 * h + 1) * count_a(t)

  defp count_b([h, _]), do: h

  ### r = k(mm - nn)形式
  defp count_b([h | t]) do
    r1 = count_b(t)
    r2 = 3 * r1 + 1
    r2 + (h - 1) * (2 * r1 + 1)
  end

  ### prime list to num
  def list2num(list), do: l2n(Enum.reverse(list), @ps, 1)

  defp l2n([], _, acc), do: acc
  defp l2n([h | t], [ph | pt], acc), do: l2n(t, pt, acc * pow(ph, h))

  defp pow(a, b), do: :math.pow(a, b) |> round()

  def now(), do: :os.system_time(:milli_seconds)
  ##### search
  def search() do
    start = now()

    res =
      for a <- 2..15,
          b <- 0..a,
          c <- 0..b,
          d <- 0..c,
          e <- 0..d,
          f <- 0..e do
        [f, e, d, c, b, a]
      end
      |> Enum.filter(fn x -> count_list(x) == @target end)
      |> Enum.map(fn x -> list2num(x) end)

    IO.inspect(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
