defmodule EulerTotientFunction do
  @moduledoc """
  欧拉函数
  小于或等于n的正整数中与n互质的数的数目
  """
  require Integer

  def euler_function(n), do: ef(n, 1, 0)
  def ef(n, index, acc) when index == n, do: acc

  def ef(n, index, acc) do
    case Integer.gcd(n, index) do
      1 -> ef(n, index + 1, acc + 1)
      _ -> ef(n, index + 1, acc)
    end
  end
end
