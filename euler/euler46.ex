defmodule Euler46 do
  @moduledoc """
  https://projecteuler.net/problem=46
  """

  require Integer

  # 素数校验
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

  ############### 素数校验工具 ##############

  defp iter(n, ps) do
    cond do
      prime?(n) -> iter(n + 2, ps)
      satisfy(n, ps) -> iter(n + 2, ps)
      :else -> n
    end
  end

  defp satisfy(n, ps) do
    c =
      ps
      |> Enum.filter(fn x -> x < n end)
      |> Enum.map(fn x -> n - x end)
      |> Enum.filter(fn x -> rem(x, 2) == 0 end)
      |> Enum.map(fn x -> div(x, 2) end)
      |> Enum.filter(fn x -> sqrt?(x) end)
      |> Enum.count()

    c > 0
  end

  defp sqrt?(x) do
    r = round(:math.sqrt(x))
    r * r == x
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    ps = 1..10000 |> Enum.filter(fn x -> prime?(x) end)
    res = iter(33, ps)
    timeuse = now() - start
    IO.puts(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
