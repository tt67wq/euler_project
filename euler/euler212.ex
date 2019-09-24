defmodule Euler212 do
  @moduledoc false

  def init, do: :ets.new(:lagged_fibonacci, [:named_table])

  defp cache_lfg(k) do
    case :ets.lookup(:lagged_fibonacci, k) do
      [] ->
        v = lagged_fibonacci_generator(k)
        :ets.insert(:lagged_fibonacci, {k, v})
        v

      [{^k, value}] ->
        value
    end
  end

  def lagged_fibonacci_generator(k) when k <= 55,
    do: rem(100_003 - 200_003 * k + 300_007 * k * k * k, 1_000_000)

  def lagged_fibonacci_generator(k) do
    r1 = cache_lfg(k - 24)
    r2 = cache_lfg(k - 55)
    rem(r1 + r2, 1_000_000)
  end

  def cube_parameter(n) do
    x0 = lagged_fibonacci_generator(6 * n - 5) |> rem(10000)
    y0 = lagged_fibonacci_generator(6 * n - 4) |> rem(10000)
    z0 = lagged_fibonacci_generator(6 * n - 3) |> rem(10000)
    dx = 1 + rem(lagged_fibonacci_generator(6 * n - 2), 399)
    dy = 1 + rem(lagged_fibonacci_generator(6 * n - 1), 399)
    dz = 1 + rem(lagged_fibonacci_generator(6 * n), 399)
    {{x0, y0, z0}, {x0 + dx, y0 + dy, z0 + dz}}
  end

  def volumn({{x0, y0, z0}, {ex0, ey0, ez0}}), do: (ex0 - x0) * (ey0 - y0) * (ez0 - z0)

  def cube_merge({{x0, _y0, _z0}, {ex0, _ey0, _ez0}}, {{x1, _y1, _z1}, {ex1, _ey1, _ez1}})
      when ex0 <= x1 or ex1 <= x0,
      do: nil

  def cube_merge({{_x0, y0, _z0}, {_ex0, ey0, _ez0}}, {{_x1, y1, _z1}, {_ex1, ey1, _ez1}})
      when ey0 <= y1 or ey1 <= y0,
      do: nil

  def cube_merge({{_x0, _y0, z0}, {_ex0, _ey0, ez0}}, {{_x1, _y1, z1}, {_ex1, _ey1, ez1}})
      when ez0 <= z1 or ez1 <= z0,
      do: nil

  def cube_merge({{x0, y0, z0}, {ex0, ey0, ez0}}, {{x1, y1, z1}, {ex1, ey1, ez1}}) do
    x2 = max(x0, x1)
    y2 = max(y0, y1)
    z2 = max(z0, z1)

    ex2 = min(ex0, ex1)
    ey2 = min(ey0, ey1)
    ez2 = min(ez0, ez1)
    {{x2, y2, z2}, {ex2, ey2, ez2}}
  end

  def pre([], acc), do: acc
  def pre([h | t], acc), do: pre(t, iter(h, t, []) ++ acc)

  defp iter(_, [], acc), do: acc

  defp iter(cube, [h | t], acc) do
    cube_merge(cube, h)
    |> case do
      nil -> iter(cube, t, acc)
      other -> iter(cube, t, [{[cube, h], other} | acc])
    end
  end

  defp loop_iter([], _, acc), do: acc

  defp loop_iter([{parents, cube} | t], cubes, acc) do
    bcc =
      cubes
      |> Enum.filter(fn x -> not Enum.member?(parents, x) end)
      |> Enum.map(fn x -> {[cube | parents], cube_merge(x, cube)} end)
      |> Enum.filter(fn {_, x} -> x != nil end)

    loop_iter(t, cubes, bcc ++ acc)
  end

  defp out_iter(merges, flag, cubes, acc) do
    next_merges = loop_iter(merges, cubes, [])
    IO.puts("merge counts: #{Enum.count(next_merges)}")

    cond do
      Enum.count(next_merges) == 0 ->
        acc

      :else ->
        dv =
          next_merges
          |> Enum.map(fn {_, x} -> volumn(x) end)
          |> Enum.sum()

        case flag do
          0 ->
            out_iter(next_merges, 1, cubes, acc + dv)

          1 ->
            out_iter(next_merges, 0, cubes, acc - dv)
        end
    end
  end

  def run do
    cubes = 1..50000 |> Enum.map(fn x -> cube_parameter(x) end)

    vs = cubes |> Enum.map(fn x -> volumn(x) end) |> Enum.sum()

    lv2 = pre(cubes, [])
    dv = lv2 |> Enum.map(fn {_, x} -> volumn(x) end) |> Enum.sum()

    IO.puts(Enum.count(lv2))
    out_iter(lv2, 0, cubes, vs - dv)
  end
end
