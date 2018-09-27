defmodule SkipList do
  @moduledoc """
  跳跃表
  """

  @max_level 10

  def new(), do: %{top_level: 0, list_map: %{0 => []}}

  # 伯努利过程
  defp bernoulli(acc) do
    # coin tossing
    case Enum.random(1..2) do
      1 -> acc
      2 -> bernoulli(acc + 1)
    end
  end

  def random_level() do
    r = bernoulli(0)

    cond do
      r > @max_level -> @max_level
      :else -> r
    end
  end

  # 搜索
  def search(sl, key), do: search(Map.fetch!(sl, :list_map), key, Map.fetch!(sl, :top_level))

  defp search(_, _, -1), do: nil

  defp search(list_map, key, level) do
    case Map.fetch(list_map, level) do
      :error ->
        # 未命中
        raise "level not exists"

      {:ok, list} ->
        v = Enum.find(list, fn x -> Map.fetch!(x, :key) == key end)

        case v do
          nil -> search(list_map, key, level - 1)
          _ -> v
        end
    end
  end

  # 是否存在
  def exists?(sl, key), do: search(sl, key) != nil

  def insert(sl, key, value) do
    case exists?(sl, key) do
      true ->
        sl

      false ->
        0..random_level()
        |> Enum.reduce(sl, fn x, acc -> insert(acc, x, key, value) end)
    end
  end

  defp insert(sl, level, key, value) do
    old_map = Map.fetch!(sl, :list_map)

    case Map.fetch(old_map, level) do
      :error ->
        # 创建一个新层

        new_map = Map.put(old_map, level, [%{key: key, value: value}])

        Map.update(sl, :top_level, 1, fn x -> x + 1 end)
        |> Map.put_new(sl, :list_map, new_map)

      {:ok, list} ->
        new_list =
          [%{key: key, value: value} | list]
          |> Enum.sort_by(fn x -> Map.fetch!(x, :key) end)

        new_map = Map.put(old_map, level, new_list)
        Map.put(sl, :list_map, new_map)
    end
  end
end
