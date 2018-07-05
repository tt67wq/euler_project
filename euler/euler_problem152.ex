defmodule Euler152 do
  @moduledoc """
  https://projecteuler.net/problem=152
  """
  require Logger
  require Integer
  use Bitwise

  @type int :: non_neg_integer
  @type ints :: [int]

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

  @spec lcm(int, int) :: int
  def lcm(a, b), do: div(a * b, Integer.gcd(a, b))

  @spec lcm_list(ints) :: int
  def lcm_list(list), do: lcl(list, 1)
  defp lcl([], acc), do: acc
  defp lcl([h | t], acc), do: lcl(t, lcm(h, acc))

  @spec all_sums(ints) :: map()
  def all_sums(list), do: allsums(list, %{0 => 1})

  defp allsums([], combos), do: combos

  defp allsums([h | t], combos) do
    ncombos =
      Map.to_list(combos)
      |> Enum.reduce(combos, fn {t, n}, acc -> Map.update(acc, t + h, n, &(&1 + n)) end)

    allsums(t, ncombos)
  end

  def denoimator_filter(denoimator) do
  end

  def sqrt(x), do: :math.sqrt(x) |> round()

  def solution() do
    # base = Enum.to_list(2..80)
    denoimators = 2..80 |> Enum.map(fn x -> x * x end)
    d = lcm_list(denoimators)
    inverse = Enum.map(denoimators, fn x -> div(d, x) end)
    target = div(d, 2)

    # [_ | t] = inverse
    # left = all_sums(inverse |> Enum.take_every(2))
    # right = all_sums(t |> Enum.take_every(2))

    # left
    # |> Map.to_list()
    # |> Enum.map(fn {x, n} ->
    #   case Map.fetch(right, target - x) do
    #     {:ok, v} -> v * n
    #     :error -> 0
    #   end
    # end)
    # |> Enum.sum()
  end
end
