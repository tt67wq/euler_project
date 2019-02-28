defmodule Kruskal do
  @moduledoc """
  最小生成树算法
  """
  require Logger

  def init do
    %{
      :a => %{:b => 7, :d => 5},
      :b => %{:a => 7, :c => 8, :d => 9, :e => 7},
      :c => %{:b => 8, :e => 5},
      :d => %{:a => 5, :b => 9, :e => 15, :f => 6},
      :e => %{:b => 7, :c => 5, :d => 15, :f => 8, :g => 9},
      :f => %{:d => 6, :e => 8, :g => 11},
      :g => %{:f => 11, :e => 9}
    }
  end

  defp path_set(mp) do
    Map.to_list(mp)
    |> Enum.map(fn {k, v} -> {k, Map.to_list(v)} end)
    |> Enum.reduce([], fn {k, list}, acc ->
      acc ++ Enum.map(list, fn {z, v} -> {Enum.sort([z, k]), v} end)
    end)
    |> Enum.uniq()
    |> Enum.sort_by(fn {_, v} -> v end)
  end

  ## 获取包含p点的集合
  defp get_cluster(p, bcc) do
    ps = Enum.filter(bcc, fn x -> Enum.member?(x, p) end)

    case ps do
      [] -> [p]
      [r] -> r
    end
  end

  # p1 p2 是否联通，即加入后形成圈
  defp in_same_tree?(p1, p2, bcc) do
    c1 = get_cluster(p1, bcc)
    c2 = get_cluster(p2, bcc)

    # Logger.info("#{p1}, #{p2}, #{inspect c1}, #{inspect c2}")
    cond do
      c1 == c2 ->
        # 联通
        :error

      :else ->
        # merge
        nbcc =
          Enum.filter(bcc, fn x -> x != c1 end)
          |> Enum.filter(fn x -> x != c2 end)

        {:ok, [c1 ++ c2 | nbcc]}
    end
  end

  defp kru_iter([], acc, _), do: acc

  defp kru_iter([{[p1, p2], k} | t], acc, bcc) do
    case in_same_tree?(p1, p2, bcc) do
      :error ->
	Logger.info("#{p1}, #{p2} in same tree")
        kru_iter(t, acc, bcc)

      {:ok, nbcc} ->
        nacc =
          Map.update(acc, p1, %{p2 => k}, fn x -> Map.put(x, p2, k) end)
          |> Map.update(p2, %{p1 => k}, fn x -> Map.put(x, p1, k) end)

        kru_iter(t, nacc, nbcc)
    end
  end

  def test do
    init()
    |> path_set()
    |> kru_iter(%{}, [])
  end
end
