defmodule Euler168 do
  @moduledoc """
  https://projecteuler.net/problem=168
  """

  require Integer

  def pow(_, 0), do: 1
  def pow(x, n) when Integer.is_odd(n), do: x * pow(x, n - 1)

  def pow(x, n) do
    result = pow(x, div(n, 2))
    result * result
  end

  defp num_length(num), do: Integer.to_string(num) |> String.length()

  defp rotate(num), do: rem(num, 10) * pow(10, num_length(num) - 1) + div(num, 10)

  def get_rotate_division_nums(0), do: []

  def get_rotate_division_nums(m) do
    1..9
    |> Enum.map(fn x ->
      {x,
       {div(pow(10, m) * (x + 1), pow(10, m + 1) + x),
        div(pow(10, m - 1) * (10 * x + 1), pow(10, m) + x)}}
    end)
    |> Enum.map(fn {y, {s, e}} -> {y, (s + 1)..e |> Enum.to_list()} end)
    |> Enum.map(fn {y, list} ->
      {y,
       Enum.reduce(list, [], fn k, acc ->
         t = div(pow(10, m) - k, 10 * k - 1)
         Enum.to_list((y * t)..(y * (t + 1))) ++ acc
       end)
       |> Enum.filter(fn z -> z >= pow(10, m - 1) end)}
    end)
    |> Enum.map(fn {y, list} -> Enum.map(list, fn x -> 10 * x + y end) end)
    |> Enum.map(fn list -> Enum.filter(list, fn x -> rem(rotate(x), x) == 0 end) end)
    |> List.flatten()
    |> Enum.uniq()
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      1..99
      |> Enum.map(fn x -> get_rotate_division_nums(x) end)
      |> Enum.map(fn list -> Enum.sum(list) end)
      |> Enum.sum()
      |> rem(100_000)

    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
