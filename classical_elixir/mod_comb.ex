defmodule ModComb do
  @moduledoc """
  快速求排列组合C（m，n）%mod
  """
  require Logger
  require Integer

  # 同余定理
  def pow_mod(m, 1, k), do: Integer.mod(m, k)
  def pow_mod(m, 2, k), do: Integer.mod(m * m, k)

  def pow_mod(m, n, k) do
    t = Integer.mod(m, k)

    cond do
      t == 0 ->
        0

      :else ->
        cond do
          Integer.is_even(n) ->
            pow_mod(m, 2, k) |> pow_mod(div(n, 2), k)

          :else ->
            ((pow_mod(m, 2, k) |> pow_mod(div(n - 1, 2), k)) * t) |> Integer.mod(k)
        end
    end
  end

  @doc """
  扩展欧几里得算法求逆元
  """
  def extend_gcd(a, b), do: eg(a, b, {0, 1}, {1, 0})
  defp eg(a, 0, {_, lx}, {_, ly}), do: {lx, ly, a}

  defp eg(a, b, {x, lx}, {y, ly}) do
    quotient = div(a, b)
    eg(b, rem(a, b), {lx - quotient * x, x}, {ly - quotient * y, y})
  end

  def niyuan(a, b) do
    {g, _, _} = extend_gcd(a, b)

    cond do
      g > 0 -> g
      :else -> b + g
    end
  end

  def factorial_mod(n, m), do: fm(n, m, 1, [1]) |> Enum.reverse()
  defp fm(n, _m, index, acc) when index == n, do: acc
  defp fm(n, m, index, [h | _] = acc), do: fm(n, m, index + 1, [rem(h * index, m) | acc])

  def comb(n, r, m) do
    ms = factorial_mod(n + 10, m)
    Logger.info(fn -> inspect(ms) end)
    x1 = niyuan(Enum.at(ms, r), m)
    x2 = rem(Enum.at(ms, n) * x1, m)
    x3 = niyuan(Enum.at(ms, n - r), m)
    Logger.info("#{x1}, #{x2}, #{x3}")
    rem(x2 * x3, m)
  end
end
