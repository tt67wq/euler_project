defmodule Euler153 do
  @moduledoc """
  https://projecteuler.net/problem=153

  参考资料
  https://en.wikipedia.org/wiki/Gaussian_integer
  """

  require Integer
  require Logger

  @limit 100_000_000

  defp func1(_a, _b, _index, _base, bcc, acc) when bcc > @limit, do: acc

  defp func1(a, b, index, base, bcc, acc) do
    # 需要确定a+bi在1..@limit中出现的次数
    # 以limit为6为例子
    # 1+i  出现3次
    # 2+2i 出现1次
    # 3+3i 出现1次
    # 1+2i 2+1i 各出现一次
    func1(
      a,
      b,
      index + 1,
      base,
      bcc + base,
      acc + a * index * 2 * div(@limit, bcc)
    )
  end

  def sum_fac(num), do: sf(num, 1, 0)
  defp sf(num, index, acc) when index > num, do: acc

  defp sf(num, index, acc), do: sf(num, index + 1, div(num, index) * index + acc)
  def sl(a, 1, acc) when a * a + 1 > @limit, do: acc
  def sl(a, b, acc) when b > a, do: sl(a + 1, 1, acc)

  def sl(a, b, acc) do
    # Logger.info("#{a}, #{b}, #{acc}")

    case Integer.gcd(a, b) do
      1 ->
        t = a * a + b * b

        cond do
          t > @limit ->
            sl(a + 1, 1, acc)

          :else ->
            s =
              case a do
                ^b -> func1(a, a, 1, t, t, 0)
                _ -> func1(a, b, 1, t, t, 0) + func1(b, a, 1, t, t, 0)
              end

            sl(a, b + 1, s + acc)
        end

      _ ->
        sl(a, b + 1, acc)
    end
  end

  def solution() do
    sl(1, 1, 0) + sum_fac(@limit)
  end
end
