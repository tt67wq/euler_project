defmodule MillerRabin do
  @moduledoc """
  Miller-Rabin素数判定方法
  a(p−1)≡1(mod p)
  如果p是奇素数，则 x2≡1(mod p)的解为x≡1或x≡p−1(mod p)
  """
  require Integer
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

  # ======== check =========
  def prime2?(1), do: false
  def prime2?(2), do: true
  def prime2?(n), do: prime2?(n, 2)

  defp prime2?(n, index) when index * index > n, do: true

  defp prime2?(n, index) do
    case rem(n, index) do
      0 -> false
      _ -> prime2?(n, index + 1)
    end
  end

  def check(n) do
    cond do
      prime?(n) == prime2?(n) ->
        check(n + 1)

      :else ->
        IO.puts("#{n}, check wrong, res => #{prime?(n)}")
    end
  end
end
