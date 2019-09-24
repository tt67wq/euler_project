defmodule Euler60 do
  @moduledoc """
  https://projecteuler.net/problem=60
  """
  require Integer
  require Logger

  #### 素数校验工具 BEGIN
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

  #### 素数校验工具 END

  ### 乘方
  def pow(_, 0), do: 1
  def pow(x, n) when Integer.is_odd(n), do: x * pow(x, n - 1)

  def pow(x, n) do
    result = pow(x, div(n, 2))
    result * result
  end

  def num_concat(a, b) do
    bl = num_length(b)
    a * pow(10, bl) + b
  end

  defp num_length(a), do: nl(a, 0)
  defp nl(0, acc), do: acc
  defp nl(a, acc), do: nl(div(a, 10), acc + 1)

  defp search([], _), do: nil

  defp search([h | t], ns) do
    f = Enum.find(ns, fn x -> not (prime?(num_concat(x, h)) and prime?(num_concat(h, x))) end)

    case f do
      nil -> h
      _ -> search(t, ns)
    end
  end

  def dfs(_ps, 0, _, acc), do: acc

  def dfs(_, _, _, []), do: nil

  def dfs(ps, deep, progress, [ah | at] = acc) do
    # Logger.info("#{inspect(acc)}")

    n =
      Enum.filter(ps, fn x -> x > progress end)
      |> search(acc)

    case n do
      nil ->
        # 回溯
        dfs(ps, deep + 1, ah, at)

      _ ->
        # 继续
        dfs(ps, deep - 1, n, [n | acc])
    end
  end

  @spec now() :: integer()
  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    ps = 1..10000 |> Enum.filter(fn x -> prime?(x) end)
    # 求的是最小和，用dfs可能有点问题
    # 3, 7, 11 都没找到，试到13的时候找到了

    nums = dfs(ps, 4, 3, [13])

    sum = Enum.sum(nums)

    IO.inspect(nums)
    IO.puts("sum => #{sum}")

    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
