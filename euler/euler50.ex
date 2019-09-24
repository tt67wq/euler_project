defmodule Euler50 do
  @moduledoc """
  http://pe-cn.github.io/50/
  """
  require Integer
  require Logger

  @top 1_000_000
  @limit 5000

  # ==== prime check begin ====
  def prime?(1), do: false
  def prime?(2), do: true
  def prime?(n), do: prime?(n, 2)

  defp prime?(n, index) when index * index > n, do: true

  defp prime?(n, index) do
    case rem(n, index) do
      0 -> false
      _ -> prime?(n, index + 1)
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
