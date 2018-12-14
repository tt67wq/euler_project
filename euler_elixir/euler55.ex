defmodule Euler55 do
  @moduledoc """
  https://projecteuler.net/problem=55
  """
  @limit 50

  @doc """
  是否为回文数
  """
  @spec palindrome?(Integer) :: boolean
  def palindrome?(number), do: number_reverse(number) == number

  @doc """
  数字调转
  """
  @spec number_reverse(Integer) :: Integer
  def number_reverse(number), do: nr(number, 0)
  defp nr(0, acc), do: acc
  defp nr(num, acc), do: nr(div(num, 10), acc * 10 + rem(num, 10))

  @doc """
  数字和它的反转数字和
  """
  def reverse_sum(number), do: number + number_reverse(number)

  def lychrel?(number), do: lychrel(number, 1)
  defp lychrel(_number, index) when index == @limit, do: true

  defp lychrel(number, index) do
    r = reverse_sum(number)

    cond do
      palindrome?(r) -> false
      :else -> lychrel(r, index + 1)
    end
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    res = 1..10000 |> Enum.filter(fn x -> lychrel?(x) end) |> Enum.count()
    timeuse = now() - start
    IO.puts(res)
    IO.puts("timeuse ==> #{timeuse} milliseconds")
  end
end
