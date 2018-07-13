defmodule Euler152 do
  @moduledoc """
  https://projecteuler.net/problem=152
  2 3 4 5 6 7 8 9 10 12 13 14 15 18 20 21 24 28 30 35 36 39 40 42 45 52 56 60 63 64 70 72
  """
  require Logger
  require Integer
  use Bitwise

  @type int :: non_neg_integer
  @type ints :: [int]

  # ====================== utils ======================

  @doc """
  质数校验
  """
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

  @doc """
  Generate combinations based on given collection.
  ## Examples
      iex> 1..3 |> Combination.combine(2)
      [[3, 2], [3, 1], [2, 1]]
  """
  @spec combine(Enum.t(), non_neg_integer) :: [list]
  def combine(collection, k) when is_integer(k) and k >= 0 do
    list = Enum.to_list(collection)
    list_length = Enum.count(list)

    if k > list_length do
      raise Enum.OutOfBoundsError
    else
      do_combine(list, list_length, k, [], [])
    end
  end

  defp do_combine(_list, _list_length, 0, _pick_acc, _acc), do: [[]]
  # optimization
  defp do_combine(list, _list_length, 1, _pick_acc, _acc), do: list |> Enum.map(&[&1])

  defp do_combine(list, list_length, k, pick_acc, acc) do
    list
    |> Stream.unfold(fn [h | t] -> {{h, t}, t} end)
    |> Enum.take(list_length)
    |> Enum.reduce(acc, fn {x, sublist}, acc ->
      sublist_length = Enum.count(sublist)
      pick_acc_length = Enum.count(pick_acc)

      if k > pick_acc_length + 1 + sublist_length do
        # insufficient elements in sublist to generate new valid combinations
        acc
      else
        new_pick_acc = [x | pick_acc]
        new_pick_acc_length = pick_acc_length + 1

        case new_pick_acc_length do
          ^k -> [new_pick_acc | acc]
          _ -> do_combine(sublist, sublist_length, k, new_pick_acc, acc)
        end
      end
    end)
  end

  @doc """
  选取所有的子集
  """
  def all_subset(list) do
    2..length(list) |> Enum.reduce([], fn x, acc -> combine(list, x) ++ acc end)
  end

  # ====================== main ======================

  @spec all_sums(ints) :: map()
  def all_sums(list), do: allsums(list, %{0 => 1})

  defp allsums([], combos), do: combos

  defp allsums([h | t], combos) do
    ncombos =
      Map.to_list(combos)
      |> Enum.reduce(combos, fn {t, n}, acc -> Map.update(acc, t + h, n, &(&1 + n)) end)

    allsums(t, ncombos)
  end

  def sqrt(x), do: :math.sqrt(x) |> round()

  def my_sum(list), do: list |> Enum.map(fn {_, x} -> x end) |> Enum.sum()

  @doc """
  检验素数p及其80以下的倍数是否存在可组成1/2的可能
  """
  def filter_prime(p) do
    Logger.info(p)
    list = 1..div(80, p) |> Enum.map(fn x -> x * x end)

    suv =
      case list do
        [1] ->
          []

        _ ->
          d = lcm_list(list)
          mds = Enum.map(list, fn x -> {x, div(d, x) |> rem(p * p)} end)

          all_subset(mds)
          |> Enum.filter(fn x -> rem(my_sum(x), p * p) == 0 end)
          |> Enum.reduce([], fn ls, acc -> Enum.map(ls, fn {x, _} -> x end) ++ acc end)
          |> Enum.uniq()
          |> Enum.map(fn x -> sqrt(x) * p end)
      end

    1..div(80, p) |> Enum.filter(fn x -> not Enum.member?(suv, x * p) end)
    |> Enum.map(fn x -> x * p end)
  end

  def list_sub(ls1, ls2), do: Enum.filter(ls1, fn x -> not Enum.member?(ls2, x) end)

  def solution() do
    base = 5..80 |> Enum.filter(fn x -> prime?(x) end)
    |> Enum.reduce(2..80, fn x, acc -> list_sub(acc, filter_prime(x)) end)
    denoimators = base |> Enum.map(fn x -> x * x end)
    d = lcm_list(denoimators)
    inverse = Enum.map(denoimators, fn x -> div(d, x) end)
    target = div(d, 2)

    [_ | t] = inverse
    left = all_sums(inverse |> Enum.take_every(2))
    right = all_sums(t |> Enum.take_every(2))

    left
    |> Map.to_list()
    |> Enum.map(fn {x, n} ->
      case Map.fetch(right, target - x) do
        {:ok, v} -> v * n
        :error -> 0
      end
    end)
    |> Enum.sum()
  end
end
