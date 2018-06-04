defmodule EinsteinProblem do
  @moduledoc """
  据说有五个不同颜色的房间排成一排，每个房间里分别住着一个不同国籍的人，每个人都喝一种特定品牌的饮料，抽一种特定品牌的烟，养一种宠物，
  没有任意两个人抽相同品牌的香烟，或喝相同品牌的饮料，或养相同的宠物，问题是谁在养鱼作为宠物？为了寻找答案，爱因斯坦给出了十五条线索：

  (1)、英国人住在红色的房子里；
  (2)、瑞典人养狗作为宠物；
  (3)、丹麦人喝茶；
  (5)、绿房子的主人喝咖啡；
  (6)、抽Pall Mall牌香烟的人养鸟；
  (7)、黄色房子里的人抽Dunhill牌香烟；
  (12)、抽BlueMaster牌香烟的人喝啤酒；
  (13)、德国人抽Prince牌香烟；

  (10)、抽Blends牌香烟的人和养猫的人相邻；
  (11)、养马的人和抽Dunhill牌香烟的人相邻;
  (14)、挪威人和住在蓝房子的人相邻；
  (15)、抽Blends牌香烟的人和喝矿泉水的人相邻。

  (8)、住在中间那个房子里的人喝牛奶；
  (9)、挪威人住在第一个房子里面；
  (4)、绿房子紧挨着白房子，在白房子的左边；


  solution

  [
    %{
      "cigaret" => "dunhill",
      "color" => "yellow",
      "drink" => "water",
      "nation" => "Norway",
      "pet" => "cat"
    },
    %{
      "cigaret" => "blends",
      "color" => "blue",
      "drink" => "tea",
      "nation" => "Denmark",
      "pet" => "horse"
    },
    %{
      "cigaret" => "pall mall",
      "color" => "red",
      "drink" => "milk",
      "nation" => "England",
      "pet" => "bird"
    },
    %{
      "cigaret" => "prince",
      "color" => "green",
      "drink" => "coffee",
      "nation" => "Germany",
      "pet" => "fish"
    },
    %{
      "cigaret" => "bluemater",
      "color" => "white",
      "drink" => "beer",
      "nation" => "Sweden",
      "pet" => "dog"
    }
  ],
  """
  alias EinsteinProblem.Bind
  alias EinsteinProblem.Relation

  require Logger

  @binds [
    %Bind{
      first_type: "nation",
      first_value: "England",
      second_type: "color",
      second_value: "red"
    },
    %Bind{first_type: "nation", first_value: "Sweden", second_type: "pet", second_value: "dog"},
    %Bind{
      first_type: "nation",
      first_value: "Denmark",
      second_type: "drink",
      second_value: "tea"
    },
    %Bind{
      first_type: "color",
      first_value: "green",
      second_type: "drink",
      second_value: "coffee"
    },
    %Bind{
      first_type: "cigaret",
      first_value: "pall mall",
      second_type: "pet",
      second_value: "bird"
    },
    %Bind{
      first_type: "color",
      first_value: "yellow",
      second_type: "cigaret",
      second_value: "dunhill"
    },
    %Bind{
      first_type: "cigaret",
      first_value: "bluemater",
      second_type: "drink",
      second_value: "beer"
    },
    %Bind{
      first_type: "nation",
      first_value: "Germany",
      second_type: "cigaret",
      second_value: "prince"
    }
  ]

  @relation [
    %Relation{
      item_type: "cigaret",
      item_value: "blends",
      related_type: "pet",
      related_value: "cat"
    },
    %Relation{
      item_type: "pet",
      item_value: "horse",
      related_type: "cigaret",
      related_value: "dunhill"
    },
    %Relation{
      item_type: "nation",
      item_value: "Norway",
      related_type: "color",
      related_value: "blue"
    },
    %Relation{
      item_type: "cigaret",
      item_value: "blends",
      related_type: "drink",
      related_value: "water"
    },
    %Relation{
      item_type: "color",
      item_value: "white",
      related_type: "color",
      related_value: "green"
    }
  ]

  def filter_by_binds(item) do
    l =
      @binds
      |> Enum.filter(fn x -> filter_by_bind(item, x) end)
      |> length()

    l == 8
  end

  defp filter_by_bind(item, bind) do
    cond do
      Map.fetch!(item, bind.first_type) == bind.first_value and
          Map.fetch!(item, bind.second_type) != bind.second_value ->
        false

      Map.fetch!(item, bind.second_type) == bind.second_value and
          Map.fetch!(item, bind.first_type) != bind.first_value ->
        false

      :else ->
        true
    end
  end

  def filter_by_relations2(item) do
    l =
      @relation
      |> Enum.filter(fn x -> filter_by_relations2(item, x) end)
      |> length

    l == 5
  end

  defp filter_by_relations2(item, relation) do
    cond do
      Map.fetch!(item, relation.item_type) == relation.item_value and
          Map.fetch!(item, relation.related_type) == relation.related_value ->
        false

      :else ->
        true
    end
  end

  def filter_by_relations(list) do
    l =
      @relation
      |> Enum.filter(fn x -> fbr(list, x, 0) end)
      |> length()

    l == 5
  end

  defp fbr(list, relation, 0) do
    item0 = Enum.at(list, 0)
    item_right = Enum.at(list, 1)

    # Logger.info("#{inspect(item0)}")

    cond do
      Map.fetch!(item0, relation.item_type) == relation.item_value and
          Map.fetch!(item_right, relation.related_type) == relation.related_value ->
        true

      :else ->
        fbr(list, relation, 1)
    end
  end

  defp fbr(list, relation, 4) do
    item0 = Enum.at(list, 4)
    item_left = Enum.at(list, 3)

    cond do
      Map.fetch!(item0, relation.item_type) == relation.item_value and
          Map.fetch!(item_left, relation.related_type) == relation.related_value ->
        true

      :else ->
        false
    end
  end

  defp fbr(list, relation, index) do
    item0 = Enum.at(list, index)
    item_left = Enum.at(list, index - 1)
    item_right = Enum.at(list, index + 1)

    cond do
      Map.fetch!(item0, relation.item_type) == relation.item_value and
          Map.fetch!(item_left, relation.related_type) == relation.related_value ->
        true

      Map.fetch!(item0, relation.item_type) == relation.item_value and
          Map.fetch!(item_right, relation.related_type) == relation.related_value ->
        true

      :else ->
        fbr(list, relation, index + 1)
    end
  end

  def filter_by_item(items, item) do
    items
    |> Enum.filter(fn x -> Map.fetch!(x, "color") != Map.fetch!(item, "color") end)
    |> Enum.filter(fn x -> Map.fetch!(x, "nation") != Map.fetch!(item, "nation") end)
    |> Enum.filter(fn x -> Map.fetch!(x, "drink") != Map.fetch!(item, "drink") end)
    |> Enum.filter(fn x -> Map.fetch!(x, "pet") != Map.fetch!(item, "pet") end)
    |> Enum.filter(fn x -> Map.fetch!(x, "cigaret") != Map.fetch!(item, "cigaret") end)
  end

  def solution() do
    items =
      for color <- ["red", "yellow", "blue", "green", "white"],
          nation <- ["England", "Sweden", "Denmark", "Germany", "Norway"],
          drink <- ["water", "tea", "milk", "coffee", "beer"],
          pet <- ["cat", "horse", "fish", "bird", "dog"],
          cigaret <- ["dunhill", "blends", "pall mall", "prince", "bluemater"] do
        %{
          "color" => color,
          "nation" => nation,
          "drink" => drink,
          "pet" => pet,
          "cigaret" => cigaret
        }
      end
      |> Enum.filter(fn x -> filter_by_binds(x) end)
      |> Enum.filter(fn x -> filter_by_relations2(x) end)

    horse1_cands = items |> Enum.filter(fn x -> Map.fetch!(x, "nation") == "Norway" end)

    horse3_cands =
      items
      |> Enum.filter(fn x -> Map.fetch!(x, "drink") == "milk" end)
      |> Enum.filter(fn x -> Map.fetch!(x, "nation") != "Norway" end)

    for h1 <- horse1_cands,
        h3 <- horse3_cands do
      new_items =
        filter_by_item(items, h1)
        |> filter_by_item(h3)

      for h2 <- new_items,
          h4 <- new_items |> filter_by_item(h2),
          h5 <- new_items |> filter_by_item(h2) |> filter_by_item(h4) do
        [h1, h2, h3, h4, h5]
      end
    end
    |> Enum.reduce([], fn x, acc -> x ++ acc end)
    |> Enum.uniq()
    |> Enum.filter(fn x -> filter_by_relations(x) end)
  end
end
