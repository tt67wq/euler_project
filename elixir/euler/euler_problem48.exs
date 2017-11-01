defmodule SelfPowers do
  @moduledoc """
  The series, 11 + 22 + 33 + ... + 1010 = 10405071317.
  Find the last ten digits of the series, 11 + 22 + 33 + ... + 10001000.
  """

  @doc """
  阶乘求modulo
  """
  @spec power_modulo(Integer, Integer, Integer) :: Integer
  def power_modulo(x, n, m), do: pm(x, n, m, 0, 1)
  defp pm(_x, n, _m, index, acc) when index == n, do: acc
  defp pm(x, n, m, index, acc), do: pm(x, n, m, index + 1, rem(x * acc, m))

  @doc """
  和求modulo
  """
  @spec sum_modulo(Integer, Integer, Integer) :: Integer
  def sum_modulo(x, y, m), do: (rem(x, m) + rem(y, m)) |> rem(m)

  def self_powers_modulo(n, m), do: spm(n, m, 1, 0)
  defp spm(n, _m, index, acc) when index == n, do: acc
  defp spm(n, m, index, acc), do: spm(n, m, index + 1, power_modulo(index, index, m) |> sum_modulo(acc, m))
  
end
