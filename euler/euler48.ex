defmodule Euler48 do
  @moduledoc """
  The series, 11 + 22 + 33 + ... + 1010 = 10405071317.
  Find the last ten digits of the series, 11 + 22 + 33 + ... + 10001000.
  """
  require Integer

  @base 10_000_000_000

  def now(), do: :os.system_time(:milli_seconds)

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

  def run() do
    start = now()

    res =
      1..1000
      |> Enum.to_list()
      |> Enum.reduce(1, fn x, acc -> (pow_mod(x, x, @base) + acc) |> Integer.mod(@base) end)

    timeuse = now() - start

    IO.inspect(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
