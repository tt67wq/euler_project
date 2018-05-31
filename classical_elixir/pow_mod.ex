defmodule PowMod do
  require Integer
  require Logger

  def pow(_, 0), do: 1
  def pow(x, n) when Integer.is_odd(n), do: x * pow(x, n - 1)

  def pow(x, n) do
    result = pow(x, div(n, 2))
    result * result
  end

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

  def multi_mod(a, b, k) do
    m1 = Integer.mod(a, k)
    m2 = Integer.mod(b, k)

    cond do
      m1 == a and m2 == b -> Integer.mod(m1 * m2, k)
      :else -> multi_mod(m1, m2, k)
    end
  end

  def factorial_mod(0, _), do: 1
  def factorial_mod(n, m), do: fm(n, m, 1, 1)
  defp fm(n, m, index, acc) when index > n, do: rem(acc, m)
  defp fm(n, m, index, acc) when acc > m, do: fm(n, m, index, rem(acc, m))
  defp fm(n, m, index, acc), do: fm(n, m, index + 1, rem(index, m) * acc)
end
