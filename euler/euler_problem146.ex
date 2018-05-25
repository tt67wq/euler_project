defmodule Euler146 do
  @moduledoc """
  https://projecteuler.net/problem=146
  """
  @limit 150_000_000

  require Integer
  require Logger
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


  def all_prime([]), do: true

  def all_prime([h | t]) do
    cond do
      prime?(h) -> all_prime(t)
      :else -> false
    end
  end

  def ck_mod(p), do: 0..(p - 1) |> Enum.filter(fn x -> ck(x, p) end)

  defp ck(r, p) do
    res =
      [1, 3, 7, 9, 13, 27]
      |> Enum.map(fn x -> r * r + rem(x, p) end)
      |> Enum.filter(fn x -> rem(x, p) > 0 end)

    length(res) == 6
  end

  def timestamp(), do: :os.system_time(:micro_seconds)

  def solution() do
    t1 = timestamp()

    pMap =
      1..5000
      |> Enum.filter(fn x -> prime?(x) end)
      |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, x, ck_mod(x)) end)

    primes = Map.keys(pMap) |> Enum.sort()

    # res = primes |> Enum.filter(fn x -> Map.fetch!(pMap, x) == [0] end)

    res =
      sl(10, pMap, primes, [])
      |> Enum.filter(fn x -> not prime?(x * x + 19) end)
      |> Enum.filter(fn x -> not prime?(x * x + 21) end)
      |> Enum.sum()

    Logger.info("timeuse: #{timestamp() - t1} ms")
    res
  end

  defp sl(index, _, _, acc) when index > @limit, do: acc

  defp sl(index, pMap, primes, acc) do
    pass =
      primes
      |> Enum.filter(fn x -> x < index * index end)
      |> Enum.map(fn x -> {x, rem(index, x)} end)
      |> check(pMap)

    case pass do
      true ->
        cond do
          [
            index * index + 1,
            index * index + 3,
            index * index + 7,
            index * index + 9,
            index * index + 13,
            index * index + 27
          ]
          |> all_prime() ->
            Logger.info("#{index}: #{pass}")
            sl(index + 10, pMap, primes, [index | acc])

          :else ->
            sl(index + 10, pMap, primes, acc)
        end

      false ->
        sl(index + 10, pMap, primes, acc)
    end
  end

  defp check([], _), do: true

  defp check([{p, r} | t], pMap) do
    vals = Map.fetch!(pMap, p)

    cond do
      Enum.member?(vals, r) -> check(t, pMap)
      :else -> false
    end
  end
end
