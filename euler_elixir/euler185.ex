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

  def inference(mp, _, []) do
    Map.values(mp)
    |> Enum.map(fn x ->
      [h] = MapSet.to_list(x)
      h
    end)
    |> Enum.reduce(0, fn x, acc -> x + acc * 10 end)
    |> IO.puts()
  end

  def inference(mp, size, [{num, 0} | t]) do
    ds = num2digits(num)

    [choose([], ds, 1, mp)]
    |> Enum.filter(fn x -> x != nil end)
    |> Enum.map(fn x -> inference(x, size, t) end)
  end

  def inference(mp, size, [{num, hits} | t]) do
    ds = num2digits(num)

    lazy_combine(size, hits)
    |> Enum.to_list()
    |> Enum.map(fn x -> choose(x, ds, 1, mp) end)
    |> Enum.filter(fn x -> x != nil end)
    |> Enum.each(fn x -> inference(x, size, t) end)
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
    Stream.unfold(5, fn
      0 -> nil
      5 -> {10, 4}
      n -> {n, n - 1}
    end)
    |> Enum.to_list()
  end
end
