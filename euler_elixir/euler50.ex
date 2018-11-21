defmodule Euler50 do
  @moduledoc """
  http://pe-cn.github.io/50/
  """
  require Integer
  require Logger

  @top 1_000_000
  @limit 5000

  # ==== prime check begin ====

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

  # ==== prime check end ====

  defp find_prime_list([], _, acc), do: acc

  defp find_prime_list([h | t], bcc, acc) do
    s = Enum.sum([h | bcc])

    cond do
      s > @top ->
        acc

      :else ->
        case prime?(s) do
          true -> find_prime_list(t, [h | bcc], [h | bcc])
          _ -> find_prime_list(t, [h | bcc], acc)
        end
    end
  end

  defp iter([], acc), do: acc

  defp iter([h | t], acc) do
    cond do
      length(acc) * h > @top ->
        acc

      :else ->
        ps = find_prime_list(t, [h], [h])
        # Logger.info("#{h} ==> #{inspect(ps)}")

        cond do
          length(ps) > length(acc) -> iter(t, ps)
          :else -> iter(t, acc)
        end
    end
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    ps = 2..@limit |> Enum.filter(fn x -> prime?(x) end)

    res =
      iter(ps, [])
      |> Enum.sum()

    IO.puts(res)
    timeuse = now() - start
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
