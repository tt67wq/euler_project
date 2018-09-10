defmodule Euler157 do
  @moduledoc """
  https://projecteuler.net/problem=157
  """
  require Integer
  require Logger

  defp pow(a, b), do: :math.pow(a, b) |> round()

  @spec multis1(integer) :: [{integer, integer}]
  def multis1(num), do: [{1, num} | mul1(num, 0, 0, [])]

  defp mul1(_num, 10, _, acc), do: acc
  defp mul1(num, a, 10, acc), do: mul1(num, a + 1, 0, acc)
  defp mul1(num, a, b, acc) when a == 0 or b == 0, do: mul1(num, a, b + 1, acc)

  defp mul1(num, a, b, acc) do
    tmp = pow(5, a) * pow(2, b)

    cond do
      tmp == num -> mul1(num, a, b + 1, [{pow(5, a), pow(2, b)} | acc])
      :else -> mul1(num, a, b + 1, acc)
    end
  end

  @spec factors_for(integer) :: [integer]
  def factors_for(number), do: factorize(number, 2, %{})
  defp factorize(number, factor, acc) when number < factor, do: acc

  defp factorize(number, factor, acc) when rem(number, factor) == 0 do
    factorize(div(number, factor), factor, Map.update(acc, factor, 1, fn x -> x + 1 end))
  end

  defp factorize(number, factor, acc), do: factorize(number, factor + 1, acc)

  def multis2(num) do
    factors_for(num)
    |> Map.values()
    |> Enum.reduce(1, fn x, acc -> acc * (x + 1) end)
  end

  def multisum(base, num) do
    # Logger.info("#{base}, #{num}")
    multis1(num)
    |> Enum.map(fn {a, b} -> div(base, num) * (a + b) end)
    |> Enum.map(fn x -> multis2(x) end)
    |> Enum.sum()
  end

  defp now(), do: :os.system_time(:micro_seconds)

  def run() do
    start = now()

    facs = [
      1,
      2,
      4,
      5,
      8,
      10,
      16,
      20,
      25,
      32,
      40,
      50,
      64,
      80,
      100,
      125,
      128,
      160,
      200,
      250,
      256,
      320,
      400,
      500,
      512,
      625,
      640,
      800,
      1000,
      1250,
      1280,
      1600,
      2000,
      2500,
      2560,
      3125,
      3200,
      4000,
      5000,
      6250,
      6400,
      8000,
      10000,
      12500,
      12800,
      15625,
      16000,
      20000,
      25000,
      31250,
      32000,
      40000,
      50000,
      62500,
      64000,
      78125,
      80000,
      100_000,
      125_000,
      156_250,
      160_000,
      200_000,
      250_000,
      312_500,
      320_000,
      390_625,
      400_000,
      500_000,
      625_000,
      781_250,
      800_000,
      1_000_000,
      1_250_000,
      1_562_500,
      1_600_000,
      1_953_125,
      2_000_000,
      2_500_000,
      3_125_000,
      3_906_250,
      4_000_000,
      5_000_000,
      6_250_000,
      7_812_500,
      8_000_000,
      10_000_000,
      12_500_000,
      15_625_000,
      20_000_000,
      25_000_000,
      31_250_000,
      40_000_000,
      50_000_000,
      62_500_000,
      100_000_000,
      125_000_000,
      200_000_000,
      250_000_000,
      500_000_000,
      1_000_000_000
    ]

    result = iter(1, facs, 0)
    timeuse = now() - start
    IO.puts("result => #{result}, timeuse => #{timeuse} microseconds")
  end

  defp iter(10, _facs, acc), do: acc

  defp iter(index, facs, acc) do
    # Logger.info("calculating #{index}")
    base = pow(10, index)

    s =
      facs
      |> Enum.filter(fn x -> x <= base end)
      |> Enum.filter(fn x -> rem(base, x) == 0 end)
      |> Enum.map(fn x -> multisum(base, x) end)
      |> Enum.sum()

    iter(index + 1, facs, acc + s)
  end
end
