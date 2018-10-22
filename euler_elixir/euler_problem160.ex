defmodule Euler160 do
  @moduledoc """
  https://projecteuler.net/problem=160
  """
  require Integer

  @m 100000

  # 质因数分解
  @spec factorize(Integer) :: map()
  def factorize(num), do: factorize(num, 2, %{})

  defp factorize(num, index, acc) when index > num, do: acc

  defp factorize(num, index, acc) do
    case rem(num, index) do
      0 -> factorize(div(num, index), index, Map.update(acc, index, 1, fn x -> x + 1 end))
      _ -> factorize(num, index + 1, acc)
    end
  end

  defp iter([], acc), do: acc

  defp iter([h | t], acc) do
    nacc =
      factorize(h)
      |> Map.to_list()
      |> Enum.reduce(acc, fn {k, v}, acc -> Map.update(acc, k, v, fn x -> x + v end) end)

    iter(t, nacc)
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

  # defp now(), do: :os.system_time(:milli_seconds)

  defp multi_mod([], _, acc), do: acc
  defp multi_mod([h | t], k, acc), do: multi_mod(t, k, rem(acc * h, k))

  def test(x) do
    mp =
      1..x
      |> Enum.to_list()
      |> iter(%{})

    d = Map.fetch!(mp, 2) - Map.fetch!(mp, 5)

    # IO.puts(d)

    mp
    |> Map.put(2, d)
    |> Map.drop([5])
    |> Map.to_list()
    |> Enum.map(fn {p, d} -> pow_mod(p, d, @m) end)
    |> multi_mod(@m, 1)
  end

  defp ride_of(0, _), do: 0

  defp ride_of(n, p) do
    case rem(n, p) do
      0 -> ride_of(div(n, p), p)
      _ -> n
    end
  end

  def run(a, b) do
    a..b
    |> Enum.map(fn x -> ride_of(x, 2) end)
    |> Enum.map(fn x -> ride_of(x, 5) end)
    |> Enum.reduce(1, fn x, acc -> rem(x * acc, @m) end)
  end

  def no_name(tc) do
    1..@m
    |> Enum.filter(fn x -> rem(x, 5) != 0 end)
    |> ride_of_2_mod(tc, 0, 1)
  end

  defp ride_of_2_mod(list, total, index, acc) when index == total,
    do: list |> Enum.reduce(acc, fn x, bcc -> rem(x * bcc, @m) end)

  defp ride_of_2_mod([h | t], total, index, acc) do
    case rem(h, 2) do
      0 -> ride_of_2_mod([div(h, 2) | t], total, index + 1, acc)
      _ -> ride_of_2_mod(t, total, index, rem(acc * h, @m))
    end
  end
end
