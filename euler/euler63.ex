defmodule Euler63 do
  @moduledoc """
  https://projecteuler.net/problem=63
  """
  require Integer
  require Logger

  # 数字长度
  def digit_len(num), do: dl(num, 0)
  defp dl(0, acc), do: acc
  defp dl(num, acc), do: dl(div(num, 10), acc + 1)

  def pow(_, 0), do: 1
  def pow(x, n) when Integer.is_odd(n), do: x * pow(x, n - 1)

  def pow(x, n) do
    result = pow(x, div(n, 2))
    result * result
  end

  @spec now() :: integer()
  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    res = iter(1, 1, 0)
    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end

  defp iter(_, 22, acc), do: acc
  defp iter(10, p, acc), do: iter(2, p + 1, acc)

  defp iter(n, p, acc) do
    # Logger.info("#{n}, #{p}, #{acc}")
    num = pow(n, p)
    l = digit_len(num)

    cond do
      l == p ->
        iter(n + 1, p, acc + 1)

      l < p ->
        iter(n + 1, p, acc)
    end
  end
end
