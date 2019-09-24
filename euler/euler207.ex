defmodule Euler207 do
  @moduledoc false

  use Bitwise
  require Logger

  def perfects do
    [
      2,
      4,
      8,
      16,
      32,
      64,
      128,
      256,
      512,
      1024,
      2048,
      4096,
      8192,
      16384,
      32768,
      65536,
      131_072,
      262_144,
      524_288,
      1_048_576
    ]

    # 1..20
    # |> Enum.map(fn x -> round(:math.pow(2, x)) end)
  end

  def p(index) do
    r =
      (0.5 + :math.sqrt(index + 0.25))
      |> Float.floor()
      |> round()

    {Enum.find_index(perfects(), fn x -> x * x > index end), r - 1}
  end

  defp bin_search(low, high) when high - low == 1, do: high

  defp bin_search(low, high) do
    mid = (low + high) >>> 1
    {n, m} = p(mid)

    cond do
      n * 12345 < m -> bin_search(low, mid)
      :else -> bin_search(mid, high)
    end
  end

  def run do
    bin_search(185, 389_012_831_290)
  end
end
