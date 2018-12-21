defmodule Euler58 do
  @moduledoc """
  https://projecteuler.net/problem=58
  """

  ### 素数判定
  require Integer
  require Logger

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

  ### 素数判定 FINISH

  def get_cross(0), do: [1]

  def get_cross(level) do
    a = 2 * (level - 1) + 1
    b = 2 * level + 1
    s = a * a + 1
    e = b * b
    gc(level, s + 2 * level - 1, e, [])
  end

  defp gc(_level, index, e, acc) when index > e, do: acc
  defp gc(level, index, e, acc), do: gc(level, index + level * 2, e, [index | acc])

  @spec now() :: integer()
  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    level = iter(1, 1, 0)
    res = level * 2 + 1
    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end

  defp iter(level, cs, ps) do
    tps =
      get_cross(level)
      |> Enum.filter(fn x -> prime?(x) end)
      |> Enum.count()

    cond do
      (ps + tps) / (cs + 4) < 0.1 -> level
      :else -> iter(level + 1, cs + 4, ps + tps)
    end
  end
end
