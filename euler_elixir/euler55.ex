defmodule Euler55 do
  @moduledoc """
  https://projecteuler.net/problem=55
  """
  @limit 50

  @spec palindrome?(integer()) :: boolean
  def palindrome?(number), do: number_reverse(number) == number


  @spec number_reverse(integer()) :: integer()
  def number_reverse(number), do: nr(number, 0)
  defp nr(0, acc), do: acc
  defp nr(num, acc), do: nr(div(num, 10), acc * 10 + rem(num, 10))


  @spec reverse_sum(integer()) :: integer()
  def reverse_sum(number), do: number + number_reverse(number)

  @spec lychrel?(integer()) :: boolean()
  def lychrel?(number), do: lychrel(number, 1)
  defp lychrel(_number, index) when index == @limit, do: true

  defp lychrel(number, index) do
    r = reverse_sum(number)

    cond do
      palindrome?(r) -> false
      :else -> lychrel(r, index + 1)
    end
  end

  @spec now() :: integer()
  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    res = 1..10000 |> Enum.filter(fn x -> lychrel?(x) end) |> Enum.count()
    timeuse = now() - start
    IO.puts(res)
    IO.puts("timeuse ==> #{timeuse} milliseconds")
  end
end
