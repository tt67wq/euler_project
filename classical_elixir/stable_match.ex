defmodule StableMatch do
  @moduledoc """
  有N男N女，每个人都按照他对异性
  的喜欢程度排名。现在需要写出一个算法安排这N个男的、N个女的结婚，要求
  两个人的婚姻应该是稳定的。何为稳定？有两对夫妻M1 F2，M2 F1。M1心目中
  更喜欢F1，但是他和F2结婚了，M2心目中更喜欢F2，但是命运却让他和F1结婚
  了，显然这样的婚姻是不稳定的，随时都可能发生M1和F1私奔或者M2和F2私奔
  的情况。所以在做出匹配选择的时候（也就是结婚的时候），我们需要做出稳
  定的选择，以防这种情况的发生。

  算法步骤描述：

  第一轮，每个男人都选择自己名单上排在首位的女人，并向她表白。这种时候会出现两种情况：
  （1）该女士还没有被男生追求过，则该女士接受该男生的请求。
  （2）若该女生已经接受过其他男生的追求，那么该女生会将该男士与她的现任男友进行比较，若更喜欢她的男友，那么拒绝这个人的追求，否则，抛弃其男友
  第一轮结束后，有些男人已经有女朋友了，有些男人仍然是单身。
  在第二轮追女行动中，每个单身男都从所有还没拒绝过他的女孩中选出自己最中意的那一个，并向她表白，不管她现在是否是单身。
  这种时候还是会遇到上面所说的两种情况，还是同样的解决方案。直到所有人都不在是单身。
  """
  require Logger

  @doc """
  生成基本测试数据
  """
  def generate_base_data() do
    men_names = ["a", "b", "c", "d", "e", "f", "g", "h"]
    women_names = ["A", "B", "C", "D", "E", "F", "G", "H"]
    men_map = %{}
    women_map = %{}

    men =
      men_names
      |> Enum.reduce(men_map, fn x, acc -> Map.put(acc, x, {"", Enum.shuffle(women_names)}) end)

    women =
      women_names
      |> Enum.reduce(women_map, fn x, acc -> Map.put(acc, x, {"", Enum.shuffle(men_names)}) end)

    {men, women}
  end

  @doc """
  男人对女人展开追求
  """
  def choose(women, men, women_name, men_name) do
    {hus, range} = Map.fetch!(women, women_name)
    {_, range1} = Map.fetch!(men, men_name)

    case hus do
      "" ->
        # 单身的情况
        women = Map.put(women, women_name, {men_name, range})
        men = Map.put(men, men_name, {women_name, range1})
        {women, men}

      _ ->
        {_, range2} = Map.fetch!(men, hus)

        case compare(range, hus, men_name) do
          :better ->
            # 如果追求者比现任好，则更换现任
            women = Map.put(women, women_name, {men_name, range})
            men = Map.put(men, men_name, {women_name, range1})
            men = Map.put(men, hus, {"", range2 |> Enum.filter(fn x -> x != women_name end)})
            {women, men}

          :worse ->
            # 不如现任
            men = Map.put(men, men_name, {"", range1 |> Enum.filter(fn x -> x != women_name end)})

            {women, men}
        end
    end
  end

  # 比较两个男人在队列中的位置
  defp compare([hus | _t], hus, _men_name), do: :worse
  defp compare([men_name | _t], _, men_name), do: :better
  defp compare([_ | t], hus, men_name), do: compare(t, hus, men_name)

  @doc """
  所有单身狗对名单上的女人展开追求
  """
  def iter(women, men) do
    ["a", "b", "c", "d", "e", "f", "g", "h"]
    |> Enum.map(fn x -> {x, Map.fetch!(men, x)} end)
    |> Enum.filter(fn {_, {cp, _}} -> cp == "" end)
    |> Enum.map(fn {m, {_, [h | _]}} -> {m, h} end)
    |> Enum.reduce({women, men}, fn {m, w}, {a, b} -> choose(a, b, w, m) end)
  end

  def solution() do
    {men, women} = generate_base_data()
    Logger.info("初始数据：")
    Logger.info(fn -> inspect(women, pretty: true, limit: 30000) end)
    Logger.info(fn -> inspect(men, pretty: true, limit: 30000) end)
    Logger.info("匹配结果：")
    sl(women, men)
  end

  defp sl(women, men) do
    {a, b} = iter(women, men)

    cond do
      a == women and b == men -> {a, b}
      :else -> sl(a, b)
    end
  end
end
