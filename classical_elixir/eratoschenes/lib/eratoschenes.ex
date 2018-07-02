defmodule Eratoschenes do
  @moduledoc """
  Documentation for Eratoschenes.
  """

  # alias Eratoschenes.Cache
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

  @doc """
  获得下一个质数
  """
  def next_prime(2), do: 3
  def next_prime(x) do
    cond do
      Integer.is_even(x) -> np(x + 1)
      :else -> np(x + 2)
    end
  end
  defp np(y) do
    cond do
      prime?(y) -> y
      :else -> np(y + 2)
    end
  end


  @doc """
  获得小于n的所有素数
  """
  def get_primes_before(n) do
    data = 2..n |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, x, true) end)
    root = :math.sqrt(n) |> round()

    2..root
    |> Enum.filter(fn x -> prime?(x) end)
    |> Enum.reduce(data, fn x, acc -> filtrate(2 * x, x, n, acc) end)
    |> Map.to_list()
    |> Enum.filter(fn {_, x} -> x end)
    |> Enum.map(fn {x, _} -> x end)
  end

  defp filtrate(index, _p, n, data) when index > n, do: data
  defp filtrate(index, p, n, data), do: filtrate(index + p, p, n, Map.put(data, index, false))

  @doc """
  质因数分解
  """
  @spec factorization(integer) :: map
  def factorization(n), do: fac(n, 2, [])
  defp fac(n, index, acc) when index * index > n and n > 1, do: list2map([n | acc])

  defp fac(n, index, acc) do
    case rem(n, index) == 0 do
      true -> fac(div(n, index), index, [index | acc])
      _ -> fac(n, next_prime(index), acc)
    end
  end

  def list2map(lst), do: list2map(lst, %{})
  defp list2map([], acc), do: acc

  defp list2map([h | t], acc) do
    case Map.fetch(acc, h) do
      {:ok, c} -> list2map(t, Map.update(acc, h, c, &(&1 + 1)))
      :error -> list2map(t, Map.update(acc, h, 1, &(&1 + 1)))
    end
  end

  @doc """
  获取num的因数个数
  """
  def get_fac_num(num) do
    num
    |> factorization
    |> Map.values()
    |> Enum.reduce(1, fn x, acc -> acc * (x + 1) end)
  end
end
