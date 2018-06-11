defmodule SkipList do
  @moduledoc """
  跳跃表的elixir实现
  """
  alias SkipList.Node
  alias SkipList.List
  require Logger

  # 最大层数限制
  @max_level 10

  @doc """
  创建跳跃表, level较高的在前面 
  """
  def new_sl(),
    do: %List{
      top_level: 0,
      list_map: %{0 => []}
    }

  @doc """
  生成一个层
  """
  def random_level() do
    r = rlevel(0)

    cond do
      r > @max_level -> @max_level
      :else -> r
    end
  end

  defp rlevel(acc) do
    r = Enum.random(1..2)

    case r do
      1 -> acc
      2 -> rlevel(acc + 1)
    end
  end

  def search_pos([], _key), do: :error

  def search_pos([h | t], key) do
    cond do
      h.key < key -> search_pos(t, key)
      h.key == key -> {:ok, h}
      :else -> :error
    end
  end

  defp insert_into_list(sl, level, key, value) do
    case Map.fetch(sl.list_map, level) do
      :error ->
        # 空level
        %List{
          top_level: sl.top_level + 1,
          list_map: Map.put(sl.list_map, level, [%Node{key: key, value: value}])
        }

      {:ok, list} ->
        # 更新
        nlist =
          [%Node{key: key, value: value} | list]
          |> Enum.sort_by(fn x -> x.key end)

        # |> Enum.uniq_by(fn %Node{key: k, value: _} -> k end)

        %List{
          top_level: sl.top_level,
          list_map: Map.put(sl.list_map, level, nlist)
        }
    end
  end

  defp delete_from_list(sl, level, key) do
    case Map.fetch(sl.list_map, level) do
      :error ->
        raise "level not exists"

      {:ok, list} ->
        nlist = df_list(list, key, [])

        case length(nlist) do
          0 ->
            if level == sl.top_level do
              %List{
                top_level: sl.top_level - 1,
                list_map: Map.delete(sl.list_map, level)
              }
            else
              # rebuild
              nmap =
                (level + 1)..sl.top_level
                |> Enum.map(fn x -> {x, Map.fetch!(sl.list_map, x)} end)
                |> Enum.reduce(sl.list_map, fn {x, l}, acc -> Map.put(acc, x - 1, l) end)

              %List{
                top_level: sl.top_level - 1,
                list_map: nmap
              }
            end

          _ ->
            %List{
              top_level: sl.top_level,
              list_map: Map.put(sl.list_map, level, nlist)
            }
        end
    end
  end

  defp df_list([h | t], key, acc) do
    cond do
      h.key < key -> df_list(t, key, [h | acc])
      h.key == key -> Enum.reverse(t) ++ acc
      :else -> Enum.reverse([h | t]) ++ acc
    end
  end

  @doc """
  从表中插入一个元素
  """
  def insert(sl, key, value) do
    # 重复的不能插入
    if exists?(sl, key) do
      :error
    end

    # 更新位置标记位
    k = random_level()

    cond do
      k > sl.top_level ->
        0..k
        |> Enum.reduce(sl, fn x, acc -> insert_into_list(acc, x, key, value) end)

      :else ->
        0..sl.top_level
        |> Enum.reduce(sl, fn x, acc -> insert_into_list(acc, x, key, value) end)
    end
  end

  @doc """
  查询
  """
  def search(sl, key), do: search(sl.list_map, key, sl.top_level)
  defp search(_, _, -1), do: nil

  defp search(lmap, key, level) do
    case Map.fetch(lmap, level) do
      :error ->
        raise "level not exists"

      {:ok, list} ->
        case search_pos(list, key) do
          :error -> search(lmap, key, level - 1)
          {:ok, value} -> value
        end
    end
  end

  def exists?(sl, key), do: search(sl, key) != nil

  @doc """
  从表中删除一个元素
  """
  def delete(sl, key) do
    if not exists?(sl, key) do
      :error
    end

    # 从高往低删除
    sl.top_level..0
    |> Enum.reduce(sl, fn x, acc -> delete_from_list(acc, x, key) end)
  end

  def printSL(sl), do: printSL(sl.list_map, sl.top_level)

  defp printSL(_lmap, -1), do: IO.puts("end")

  defp printSL(lmap, level) do
    case Map.fetch(lmap, level) do
      :error ->
        raise "level not exists"

      {:ok, list} ->
        IO.inspect(list)
        printSL(lmap, level - 1)
    end
  end

  def solution() do
    sl = new_sl()

    nsl =
      1..20
      |> Enum.reduce(sl, fn x, acc -> insert(acc, x, x * x) end)

    nsl
    # search(nsl, 14)
    
    # nsl = delete(nsl, 14)
    # search(nsl, 14)
  end
end
