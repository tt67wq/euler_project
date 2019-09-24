defmodule TruncatablePrimes do
  @moduledoc """
  The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right,
  and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
  Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
  NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
  """
  require Logger

  require Integer
  def prime?(n) when n < 2, do: false
  def prime?(2), do: true
  def prime?(n) when Integer.is_even(n), do: false

  def prime?(n), do: fermat_check(n, get_u(n - 1), 3)

  defp fermat_check(_, _, 0), do: true

  defp fermat_check(n, u, s) do
    a = Enum.random(2..(n - 1))
    x = pow_mod(a, u, n)
    {flag, nx} = double_check(u, n, x)

    case flag do
      true ->
        case nx do
          1 -> fermat_check(n, u, s - 1)
          _ -> false
        end

      false ->
        false
    end
  end

  defp double_check(tu, n, x) when tu >= n, do: {true, x}

  defp double_check(tu, n, x) do
    y = Integer.mod(x * x, n)

    cond do
      y == 1 and x != 1 and x != n - 1 -> {false, 0}
      :else -> double_check(tu * 2, n, y)
    end
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

  defp get_u(u) do
    case rem(u, 2) do
      0 -> get_u(div(u, 2))
      1 -> u
    end
  end

  def leftTruncatablePrime?(x), do: left(Integer.to_charlist(x), x)

  defp left([_h | t], x) do
    cond do
      length(t) == 0 -> prime?(x)
      prime?(x) -> left(t, List.to_integer(t))
      :else -> false
    end
  end

  def rightTruncatablePrime?(x), do: right(Integer.to_charlist(x), x)

  defp right(y, x) do
    [_h | t] = Enum.reverse(y)

    cond do
      length(t) == 0 -> prime?(x)
      prime?(x) -> right(Enum.reverse(t), List.to_integer(Enum.reverse(t)))
      :else -> false
    end
  end

  def run(), do: findall(11, [])

  defp findall(x, acc) do
    cond do
      length(acc) == 11 ->
        acc

      leftTruncatablePrime?(x) and rightTruncatablePrime?(x) ->
        Logger.info(x)
        findall(x + 2, [x | acc])

      :else ->
        findall(x + 2, acc)
    end
  end
end
