defmodule Euler156 do
  @moduledoc """
  https://projecteuler.net/problem=156
  """
  require Logger
  @type int :: integer()

  defp pow(a, b), do: :math.pow(a, b) |> round()

  def ten_base_count(1, n, 1), do: pow(10, n - 1) * n + 1
  def ten_base_count(1, n, _base), do: pow(10, n - 1) * n
  def ten_base_count(m, n, base) when m > base, do: pow(10, n - 1) * n * m + pow(10, n)
  def ten_base_count(m, n, base) when m == base, do: pow(10, n - 1) * n * m + 1
  def ten_base_count(m, n, _base), do: pow(10, n - 1) * n * m

  def count_digit(n, base), do: count_digit(n, base, digit_size(n, 0), 0)

  defp count_digit(_n, _base, -1, acc), do: acc

  defp count_digit(n, base, p, acc) do
    s = pow(10, p)
    acc = acc + ten_base_count(div(n, s), p, base)

    cond do
      div(n, s) == base ->
        count_digit(rem(n, s), base, p - 1, acc + rem(n, s))

      :else ->
        count_digit(rem(n, s), base, p - 1, acc)
    end
  end

  defp digit_size(0, acc), do: acc
  defp digit_size(n, acc), do: digit_size(div(n, 10), acc + 1)

  def binary_search(lower, higher, base, pid) when higher == lower + 1 do
    cond do
      count_digit(lower, base) == lower -> send(pid, {:ok, lower})
      :else -> send(pid, {:error})
    end
  end

  def binary_search(lower, higher, base, pid) do
    mid = div(lower + higher, 2)
    lower_value = count_digit(lower, base)
    higher_value = count_digit(higher, base)
    mid_value = count_digit(mid, base)

    if mid_value >= lower and lower_value <= mid do
      binary_search(lower, mid, base, pid)
    end

    if mid_value <= higher && higher_value >= mid do
      binary_search(mid, higher, base, pid)
    end
  end

  def loop_accept(acc) do
    receive do
      {:ok, num} ->
        Logger.info("#{num}")

        if num == 80_000_000_000 do
          Logger.info("sum ==> #{Enum.sum([num | acc])}")
        end

        loop_accept([num | acc])

      {:error} ->
        loop_accept(acc)
    end
  end

  def run() do
    {:ok, pid} = Task.start_link(fn -> loop_accept([]) end)
    binary_search(1, pow(10, 12), 1, pid)
    binary_search(1, pow(10, 12), 2, pid)
    binary_search(1, pow(10, 12), 3, pid)
    binary_search(1, pow(10, 12), 4, pid)
    binary_search(1, pow(10, 12), 5, pid)
    binary_search(1, pow(10, 12), 6, pid)
    binary_search(1, pow(10, 12), 7, pid)
    binary_search(1, pow(10, 12), 8, pid)
    binary_search(1, pow(10, 12), 9, pid)
  end
end
