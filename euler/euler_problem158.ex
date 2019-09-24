defmodule Euler158 do
  @moduledoc """
  https://projecteuler.net/problem=158
  """
  require Logger
  require Integer

  ##### Start 计算组合数工具
  @doc """
  乘方
  """
  def pow(x, n) when is_integer(x) and is_integer(n) and n >= 0, do: pow(x, n, 1)

  defp pow(_x, 0, acc), do: acc
  defp pow(x, 1, acc), do: x * acc
  defp pow(x, n, acc) when rem(n, 2) == 0, do: pow(x * x, div(n, 2), acc)
  defp pow(x, n, acc) when rem(n, 2) == 1, do: pow(x * x, div(n - 1, 2), acc * x)

  @doc """
  质因数分解
  """
  @spec factorize(Integer) :: map()
  def factorize(num), do: factorize(num, 2, %{})

  defp factorize(num, index, acc) when index > num, do: acc

  defp factorize(num, index, acc) do
    case rem(num, index) do
      0 -> factorize(div(num, index), index, Map.update(acc, index, 1, fn x -> x + 1 end))
      _ -> factorize(num, index + 1, acc)
    end
  end

  def zuhe(m, n) do
    mm = fac_map(m, n, %{})
    nn = fac_map(n, n, %{})

    Map.to_list(nn)
    |> Enum.reduce(mm, fn {k, v}, acc -> Map.update(acc, k, v, fn y -> y - v end) end)
    |> Map.to_list()
    |> Enum.map(fn {k, v} -> pow(k, v) end)
    |> Enum.reduce(1, fn x, acc -> x * acc end)
  end

  defp fac_map(_, 0, acc), do: acc

  defp fac_map(n, index, acc) do
    mp = factorize(n)

    bcc =
      Map.to_list(mp)
      |> Enum.reduce(acc, fn {k, v}, acc -> Map.update(acc, k, v, fn y -> y + v end) end)

    fac_map(n - 1, index - 1, bcc)
  end

  ##### end   计算组合数工具

  def triangle(), do: triangle(1, %{})

  defp triangle(1, _acc), do: triangle(2, %{1 => [1, 0]})

  defp triangle(level, acc) when level > 25, do: acc

  defp triangle(level, acc) do
    case Map.fetch(acc, level - 1) do
      {:ok, upper} ->
        next = level_generate(upper, [level])
        triangle(level + 1, Map.put(acc, level, next))

      :error ->
        triangle(level + 1, acc)
    end
  end

  defp level_generate([0], acc), do: Enum.reverse([0 | acc])
  defp level_generate([h1, h2 | t], acc), do: level_generate([h2 | t], [h1 + h2 + 1 | acc])

  defp now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      Map.to_list(triangle())
      |> Enum.map(fn {level, list} -> {level, zuhe(26, level + 1) * Enum.sum(list)} end)

    timeuse = now() - start
    IO.inspect(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
