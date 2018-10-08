defmodule Euler159 do
  @moduledoc """
  https://projecteuler.net/problem=159
  """
  require Logger

  @limit 1_00

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

  ## 素数校验

  @spec digital_root(Integer) :: Integer
  def digital_root(num) when num < 10, do: num
  def digital_root(num), do: rem(num - 1, 9) + 1

  defp now(), do: :os.system_time(:milli_seconds)

  @spec iter(Integer, map()) :: map()
  def iter(base, origin_map), do: iter(base, 2, digital_root(base), base * 2, origin_map)

  defp iter(_base, _index, _dr, bcc, acc) when bcc > @limit, do: acc

  defp iter(base, index, dr, bcc, acc) do
    {a, list} = Map.fetch!(acc, bcc)
    b = dr + digital_root(index)

    cond do
      a < b ->
        iter(
          base,
          index + 1,
          dr,
          bcc + base,
          Map.update(acc, bcc, {a, list}, fn _ -> {b, [base, index]} end)
        )

      :else ->
        iter(base, index + 1, dr, bcc + base, acc)
    end
  end

  @spec update(map(), Integer) :: map()
  def update(origin_map, index) do
    {mdrs, list} = Map.fetch!(origin_map, index)

    nlist =
      list
      |> Enum.map(fn x -> Map.fetch!(origin_map, x) end)
      |> Enum.reduce([], fn {_, x}, acc -> x ++ acc end)
      |> Enum.filter(fn x -> x != 1 end)

    nmdrs = nlist |> Enum.reduce(0, fn x, acc -> acc + digital_root(x) end)

    Map.update(origin_map, index, {mdrs, list}, fn _ -> {nmdrs, nlist} end)
  end

  def run() do
    start = now()

    origin_map =
      1..@limit |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, x, {digital_root(x), [1, x]}) end)

    mp =
      2..div(@limit, 2)
      |> Enum.reduce(origin_map, fn x, acc -> iter(x, acc) end)

    res =
      2..(@limit - 1)
      |> Enum.reduce(mp, fn x, acc -> update(acc, x) end)
      |> Map.delete(1)
      |> Map.delete(@limit)

    # |> Map.values()
    # |> Enum.reduce(0, fn {x, _}, acc -> acc + x end)

    timeuse = now() - start
    IO.inspect(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
    res
    # Map.to_list(res)
    # |> Enum.sort()
    # |> Enum.map(fn {x, {y, _}} -> Logger.info("mdrs[#{x}] => #{y}") end)
  end
end
