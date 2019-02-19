defmodule Euler176 do
  @moduledoc """
  https://projecteuler.net/problem=176
  47547
  """

  require Integer
  require Logger

  ##### prime check begin

  def prime?(n) when n < 2, do: false
  def prime?(2), do: true
  def prime?(n) when Integer.is_even(n), do: false

  def prime?(n), do: fermat_check(n, get_u(n - 1), 5)

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

  ##### prime check end

  @spec factorize(Integer) :: map()
  def factorize(num),
    do:
      factorize(num, 2, %{})
      |> Map.to_list()
      |> Enum.sort_by(fn {k, _v} -> k end)
      |> Enum.map(fn {_k, v} -> v end)

  defp factorize(num, index, acc) when index > num, do: acc

  defp factorize(num, index, acc) do
    case rem(num, index) do
      0 -> factorize(div(num, index), index, Map.update(acc, index, 1, fn x -> x + 1 end))
      _ -> factorize(num, index + 1, acc)
    end
  end

  def count(n) do
    list =
      factorize(n)
      |> Enum.reverse()

    a = count_a(list)
    b = count_b(list)
    Logger.info("#{a}, #{b}")
    a + b
  end

  defp count_a([h]), do: h - 1
  defp count_a([h | t]), do: (2 * h + 1) * count_a(t)

  defp count_b([h, _]), do: h

  defp count_b([h | t]) do
    r1 = count_b(t)
    r2 = 3 * r1 + 1
    r2 + (h - 1) * (2 * r1 + 1)
  end
end
