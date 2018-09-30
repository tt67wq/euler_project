defmodule Euler159 do
  @moduledoc """
  https://projecteuler.net/problem=159
  """

  @doc """
  乘方
  """
  @spec pow(Integer, Integer) :: Integer
  def pow(x, n) when is_integer(x) and is_integer(n) and n >= 0, do: pow(x, n, 1)

  defp pow(_x, 0, acc), do: acc
  defp pow(x, 1, acc), do: x * acc
  defp pow(x, n, acc) when rem(n, 2) == 0, do: pow(x * x, div(n, 2), acc)
  defp pow(x, n, acc) when rem(n, 2) == 1, do: pow(x * x, div(n - 1, 2), acc * x)

  @spec factorize(Integer) :: map()
  def factorize(num), do: factorize(num, 2, %{})

  defp factorize(num, index, acc) when index > num, do: acc

  defp factorize(num, index, acc) do
    case rem(num, index) do
      0 -> factorize(div(num, index), index, Map.update(acc, index, 1, fn x -> x + 1 end))
      _ -> factorize(num, index + 1, acc)
    end
  end

  @spec digital_root(Integer) :: Integer
  def digital_root(num) when num < 10, do: num
  def digital_root(num), do: dr(num, 0)
  defp dr(0, acc), do: acc
  defp dr(num, acc), do: dr(div(num, 10), acc + rem(num, 10))

  defp now(), do: :os.system_time(:milli_seconds)
  
  def run() do
  end
end
