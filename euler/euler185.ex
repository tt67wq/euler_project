defmodule Euler185 do
  @moduledoc false

  require Logger

  def num2digits(num), do: n2d(num, [])
  defp n2d(0, acc), do: acc
  defp n2d(num, acc), do: n2d(div(num, 10), [rem(num, 10) | acc])

  def init_mp(size) do
    init_set = MapSet.new([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])

    1..size
    |> Enum.reduce(%{}, fn x, acc -> Map.put(acc, x, init_set) end)
  end

  def dfs(mp, _, []) do
    Map.values(mp)
    |> Enum.map(fn x ->
      [h] = MapSet.to_list(x)
      h
    end)
    |> Enum.reduce(0, fn x, acc -> x + acc * 10 end)
    |> IO.puts()
  end

  def dfs(mp, size, [{num, 0} | t]) do
    ds = num2digits(num)

    [choose([], ds, 1, mp)]
    |> Enum.filter(fn x -> x != nil end)
    |> Enum.map(fn x -> dfs(x, size, t) end)
  end

  def dfs(mp, size, [{num, hits} | t]) do
    ds = num2digits(num)

    lazy_combine(size, hits)
    |> Enum.to_list()
    |> Enum.map(fn x -> choose(x, ds, 1, mp) end)
    |> Enum.filter(fn x -> x != nil end)
    |> Enum.each(fn x -> dfs(x, size, t) end)
  end

  defp choose(_, [], _, mp), do: mp

  defp choose([index | rt], [h | t], index, mp) do
    # right

    set = Map.get(mp, index)

    cond do
      MapSet.member?(set, h) ->
        # fix it
        choose(rt, t, index + 1, Map.put(mp, index, MapSet.new([h])))

      :else ->
        nil
    end
  end

  defp choose(bm, [h | t], index, mp) do
    # wrong
    nset =
      Map.get(mp, index)
      |> MapSet.delete(h)

    case MapSet.size(nset) do
      0 ->
        nil

      _ ->
        choose(bm, t, index + 1, Map.put(mp, index, nset))
    end
  end

  def lazy_combine(m, n) do
    slist = Enum.to_list(1..m)

    Stream.unfold(Enum.take(slist, n), fn
      [] -> nil
      p -> {p, next_combine(m, p)}
    end)
  end

  defp next_combine(m, p), do: nc(Enum.reverse(p), m, [])
  defp nc([], _, _), do: []

  defp nc([h | t], m, acc) do
    cond do
      h == m ->
        nc(t, m - 1, [h | acc])

      :else ->
        case acc do
          [] ->
            Enum.reverse(t) ++ [h + 1]

          _ ->
            bcc =
              1..Enum.count(acc)
              |> Enum.map(fn x -> h + x + 1 end)

            Enum.reverse(t) ++ [h + 1 | bcc]
        end
    end
  end

  def test do
    traces = [
      {5_616_185_650_518_293, 2},
      {3_847_439_647_293_047, 1},
      {5_855_462_940_810_587, 3},
      {9_742_855_507_068_353, 3},
      {4_296_849_643_607_543, 3},
      {3_174_248_439_465_858, 1},
      {4_513_559_094_146_117, 2},
      {7_890_971_548_908_067, 3},
      {8_157_356_344_118_483, 1},
      {2_615_250_744_386_899, 2},
      {8_690_095_851_526_254, 3},
      {6_375_711_915_077_050, 1},
      {6_913_859_173_121_360, 1},
      {6_442_889_055_042_768, 2},
      {2_321_386_104_303_845, 0},
      {2_326_509_471_271_448, 2},
      {5_251_583_379_644_322, 2},
      {1_748_270_476_758_276, 3},
      {4_895_722_652_190_306, 1},
      {3_041_631_117_224_635, 3},
      {1_841_236_454_324_589, 3},
      {2_659_862_637_316_867, 2}
    ]

    mp = init_mp(16)
    dfs(mp, 16, traces)
  end
end
