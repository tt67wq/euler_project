defmodule Euler54 do
  @moduledoc """
  https://projecteuler.net/problem=54
  """

  @value_map %{
    "2" => 2,
    "3" => 3,
    "4" => 4,
    "5" => 5,
    "6" => 6,
    "7" => 7,
    "8" => 8,
    "9" => 9,
    "T" => 10,
    "J" => 11,
    "Q" => 12,
    "K" => 13,
    "A" => 14
  }

  @doc """
  列表中数字个数统计
  """
  @spec counter(List) :: Map
  def counter(nums),
    do: nums |> Enum.reduce(%{}, fn x, acc -> Map.update(acc, x, 1, fn x -> x + 1 end) end)

  @doc """
  是否为同花顺
  """
  @spec is_straight_flush?(MapSet, List) :: boolean
  def is_straight_flush?(suits, values) do
    is_flush?(suits) and is_straight?(values)
  end

  @doc """
  是否有四个相同数字
  """
  @spec is_four_of_akind?(List) :: boolean
  def is_four_of_akind?(lst) do
    c = lst |> counter() |> Map.values() |> Enum.sort()
    c == [1, 4]
  end

  @doc """
  是否是3带2
  """
  @spec is_full_house?(List) :: boolean
  def is_full_house?(lst) do
    c = lst |> counter() |> Map.values() |> Enum.sort()
    c == [2, 3]
  end

  @doc """
  是否为顺子
  """
  @spec is_straight?(List) :: boolean
  def is_straight?(nums), do: flush?(Enum.sort(nums))
  defp flush?([_x]), do: true

  defp flush?([h | t]) do
    [h1 | _t1] = t

    case h1 - h do
      1 -> flush?(t)
      _ -> false
    end
  end

  @doc """
  是否为同花
  """
  @spec is_flush?(List) :: boolean
  def is_flush?(suits) do
    l = suits |> Enum.reduce(MapSet.new(), fn x, acc -> MapSet.put(acc, x) end) |> MapSet.size()
    l == 1
  end

  @doc """
  是否有三个相同数字
  """
  @spec is_three_of_akind?(List) :: boolean
  def is_three_of_akind?(lst) do
    c = lst |> counter() |> Map.values() |> Enum.sort()
    c == [1, 1, 3]
  end

  @doc """
  是否有两对
  """
  @spec is_two_pairs?(List) :: boolean
  def is_two_pairs?(lst) do
    c = lst |> counter() |> Map.values() |> Enum.sort()
    c == [1, 2, 2]
  end

  @doc """
  是否有一对
  """
  def is_one_pair?(lst) do
    c = lst |> counter() |> Map.values() |> Enum.sort()
    c == [1, 1, 1, 2]
  end

  @doc """
  获得卡牌组合的等级
  """
  @spec get_level(List) :: Integer
  def get_level(cards) do
    values =
      cards
      |> Enum.map(fn x -> String.at(x, 0) end)
      |> Enum.map(fn x -> Map.fetch!(@value_map, x) end)

    suits = cards |> Enum.map(fn x -> String.at(x, -1) end)

    cond do
      is_straight_flush?(suits, values) -> 1
      is_four_of_akind?(values) -> 2
      is_full_house?(values) -> 3
      is_flush?(suits) -> 4
      is_straight?(values) -> 5
      is_three_of_akind?(values) -> 6
      is_two_pairs?(values) -> 7
      is_one_pair?(values) -> 8
      :else -> 9
    end
  end

  defp max_pair(lst) do
    c = lst |> counter()
    Map.keys(c) |> Enum.filter(fn x -> Map.fetch!(c, x) == 2 end) |> Enum.max()
  end

  defp max_threesome(lst) do
    c = lst |> counter()
    Map.keys(c) |> Enum.filter(fn x -> Map.fetch!(c, x) == 3 end) |> Enum.max()
  end

  defp max_foursome(lst) do
    c = lst |> counter()
    Map.keys(c) |> Enum.filter(fn x -> Map.fetch!(c, x) == 4 end) |> Enum.max()
  end

  def compare_level9([], []), do: nil

  def compare_level9(lst1, lst2) do
    [h1 | t1] = Enum.sort(lst1, &(&1 >= &2))
    [h2 | t2] = Enum.sort(lst2, &(&1 >= &2))

    cond do
      h1 > h2 -> 1
      h1 < h2 -> 0
      :else -> compare_level9(t1, t2)
    end
  end

  def compare_level8(lst1, lst2) do
    mp1 = max_pair(lst1)
    mp2 = max_pair(lst2)

    cond do
      mp1 > mp2 ->
        1

      mp1 < mp2 ->
        0

      :else ->
        t1 = lst1 |> Enum.filter(fn x -> x != mp1 end)
        t2 = lst2 |> Enum.filter(fn x -> x != mp2 end)
        compare_level9(t1, t2)
    end
  end

  def compare_level7(lst1, lst2) do
    mp1 = max_pair(lst1)
    mp2 = max_pair(lst2)

    cond do
      mp1 > mp2 ->
        1

      mp1 < mp2 ->
        0

      :else ->
        t1 = lst1 |> Enum.filter(fn x -> x != mp1 end)
        t2 = lst2 |> Enum.filter(fn x -> x != mp2 end)
        compare_level8(t1, t2)
    end
  end

  def compare_level6(lst1, lst2) do
    mt1 = max_threesome(lst1)
    mt2 = max_threesome(lst2)

    cond do
      mt1 > mt2 ->
        1

      mt1 < mt2 ->
        0

      :else ->
        t1 = lst1 |> Enum.filter(fn x -> x != mt1 end)
        t2 = lst2 |> Enum.filter(fn x -> x != mt2 end)
        compare_level9(t1, t2)
    end
  end

  def compare_level5(lst1, lst2), do: compare_level9(lst1, lst2)
  def compare_level4(lst1, lst2), do: compare_level9(lst1, lst2)

  def compare_level3(lst1, lst2) do
    mt1 = max_threesome(lst1)
    mt2 = max_threesome(lst2)
    mp1 = max_pair(lst1)
    mp2 = max_pair(lst2)

    cond do
      mt1 > mt2 ->
        1

      mt1 < mt2 ->
        0

      :else ->
        cond do
          mp1 > mp2 -> 1
          mp1 < mp2 -> 0
          :else -> nil
        end
    end
  end

  def compare_level2(lst1, lst2) do
    mf1 = max_foursome(lst1)
    mf2 = max_foursome(lst2)

    cond do
      mf1 > mf2 ->
        1

      mf1 < mf2 ->
        0

      :else ->
        t1 = lst1 |> Enum.filter(fn x -> x != mf1 end)
        t2 = lst2 |> Enum.filter(fn x -> x != mf2 end)
        compare_level9(t1, t2)
    end
  end

  def compare_level1(lst1, lst2), do: compare_level9(lst1, lst2)

  def compare(cards1, cards2) do
    level1 = get_level(cards1)
    level2 = get_level(cards2)

    values1 =
      cards1
      |> Enum.map(fn x -> String.at(x, 0) end)
      |> Enum.map(fn x -> Map.fetch!(@value_map, x) end)

    values2 =
      cards2
      |> Enum.map(fn x -> String.at(x, 0) end)
      |> Enum.map(fn x -> Map.fetch!(@value_map, x) end)

    cond do
      level1 < level2 ->
        1

      level1 > level2 ->
        0

      :else ->
        case level1 do
          9 -> compare_level9(values1, values2)
          8 -> compare_level8(values1, values2)
          7 -> compare_level7(values1, values2)
          6 -> compare_level6(values1, values2)
          5 -> compare_level5(values1, values2)
          4 -> compare_level4(values1, values2)
          3 -> compare_level3(values1, values2)
          2 -> compare_level2(values1, values2)
          1 -> compare_level1(values1, values2)
          _ -> nil
        end
    end
  end

  defp ten_to_five([]), do: nil

  defp ten_to_five(lst) do
    [a, b, c, d, e | t] = lst
    {[a, b, c, d, e], t}
  end

  def get_card_data_from_file(path) do
    {:ok, content} = File.read(path)

    String.split(content, "\n")
    |> Enum.map(fn x -> String.split(x) end)
    |> Enum.map(fn x -> ten_to_five(x) end)
    |> Enum.filter(fn x -> x != nil end)
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()

    res =
      get_card_data_from_file("poker.txt")
      |> Enum.map(fn {a, b} -> compare(a, b) end)
      |> Enum.filter(fn x -> x == 1 end)
      |> length()

    timeuse = now() - start
    IO.inspect(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
