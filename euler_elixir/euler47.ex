defmodule Euler47 do
  @moduledoc """
  https://projecteuler.net/problem=47
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

  @spec factorize(Integer) :: map()
  def factorize(num), do: factorize(num, 2, %{})

  defp factorize(num, index, acc) when index > num, do: acc

  defp factorize(num, index, acc) do
    case rem(num, index) do
      0 -> factorize(div(num, index), index, Map.update(acc, index, 1, fn x -> x + 1 end))
      _ -> factorize(num, index + 1, acc)
    end
  end

  def now(), do: :os.system_time(:milli_seconds)

  @doc """
  找到四个连续的有四个质因数的数字
  """
  def run() do
    start = now()
    res = find(647, [])
    timeuse = now() - start
    IO.inspect(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
  end

  defp find(_index, acc) when length(acc) == 4, do: acc

  defp find(index, acc) do
    size = factorize(index) |> Map.to_list() |> length()

    case size do
      4 -> find(index + 1, [index | acc])
      _ -> find(index + 1, [])
    end
  end
end
