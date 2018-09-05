defmodule PandigitalMultiples do
  @moduledoc """
  https://projecteuler.net/problem=38
  """
  @limit 999_999_999
  # num length
  def num_len(num), do: nl(num, 0)
  defp nl(0, acc), do: acc
  defp nl(num, acc), do: nl(div(num, 10), acc + 1)

  defp pow(a, b), do: :math.pow(a, b) |> round()

  def generate_num(seed), do: gen(seed, 1, 0)

  defp gen(_seed, 10, acc), do: acc

  defp gen(seed, index, acc) do
    tmp = seed * index
    bcc = acc * pow(10, num_len(tmp)) + tmp

    cond do
      bcc > @limit -> acc
      :else -> gen(seed, index + 1, bcc)
    end
  end

  def check(num), do: digits(num, MapSet.new()) == MapSet.new(1..9)
  defp digits(0, acc), do: acc
  defp digits(num, acc), do: digits(div(num, 10), MapSet.put(acc, rem(num, 10)))

  def now(), do: :os.system_time(:micro_seconds)

  def run() do
    start = now()

    a =
      90..99
      |> Enum.map(fn x -> generate_num(x) end)
      |> Enum.filter(fn x -> check(x) end)

    b =
      910..999
      |> Enum.map(fn x -> generate_num(x) end)
      |> Enum.filter(fn x -> check(x) end)

    c =
      9100..9999
      |> Enum.map(fn x -> generate_num(x) end)
      |> Enum.filter(fn x -> check(x) end)

    result = Enum.max(a ++ b ++ c)
    timeuse = now() - start
    IO.puts("result => #{result}, timeuse => #{timeuse} microseconds")
  end
end
