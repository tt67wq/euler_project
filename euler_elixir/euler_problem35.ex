defmodule CircularPrimes do
  @moduledoc """
  The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.
  There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
  How many circular primes are there below one million?
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
      1 -> get_u(div(u, 2))
      _ -> u
    end
  end

  defp num_len(0, acc), do: acc
  defp num_len(num, acc), do: num_len(div(num, 10), acc + 1)

  defp pow(a, b), do: :math.pow(a, b) |> round()

  def rotate(num) do
    r = rem(num, 10)
    d = div(num, 10)
    r * pow(10, num_len(d, 0)) + d
  end

  def rotations_prime?(num), do: rots(num, rotate(num))

  defp rots(num, num), do: true

  defp rots(num, rnum) do
    cond do
      prime?(rnum) -> rots(num, rotate(rnum))
      :else -> false
    end
  end

  def run() do
    2..1_000_000
    |> Enum.filter(fn x -> prime?(x) end)
    |> Enum.filter(fn x -> rotations_prime?(x) end)
    |> Enum.count()
  end
end
