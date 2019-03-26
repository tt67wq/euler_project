defmodule Euler185 do
  require Logger

  @moduledoc false

  # @filters [
  #   {[9, 0, 3, 4, 2], 2},
  #   {[7, 0, 7, 9, 4], 0},
  #   {[3, 9, 4, 5, 8], 2},
  #   {[3, 4, 1, 0, 9], 1},
  #   {[5, 1, 5, 4, 5], 2},
  #   {[1, 2, 5, 3, 1], 1}
  # ]

  @filters [
    {[5, 6, 1, 6, 1, 8, 5, 6, 5, 0, 5, 1, 8, 2, 9, 3], 2},
    {[3, 8, 4, 7, 4, 3, 9, 6, 4, 7, 2, 9, 3, 0, 4, 7], 1},
    {[5, 8, 5, 5, 4, 6, 2, 9, 4, 0, 8, 1, 0, 5, 8, 7], 3},
    {[9, 7, 4, 2, 8, 5, 5, 5, 0, 7, 0, 6, 8, 3, 5, 3], 3},
    {[4, 2, 9, 6, 8, 4, 9, 6, 4, 3, 6, 0, 7, 5, 4, 3], 3},
    {[3, 1, 7, 4, 2, 4, 8, 4, 3, 9, 4, 6, 5, 8, 5, 8], 1},
    {[4, 5, 1, 3, 5, 5, 9, 0, 9, 4, 1, 4, 6, 1, 1, 7], 2},
    {[7, 8, 9, 0, 9, 7, 1, 5, 4, 8, 9, 0, 8, 0, 6, 7], 3},
    {[8, 1, 5, 7, 3, 5, 6, 3, 4, 4, 1, 1, 8, 4, 8, 3], 1},
    {[2, 6, 1, 5, 2, 5, 0, 7, 4, 4, 3, 8, 6, 8, 9, 9], 2},
    {[8, 6, 9, 0, 0, 9, 5, 8, 5, 1, 5, 2, 6, 2, 5, 4], 3},
    {[6, 3, 7, 5, 7, 1, 1, 9, 1, 5, 0, 7, 7, 0, 5, 0], 1},
    {[6, 9, 1, 3, 8, 5, 9, 1, 7, 3, 1, 2, 1, 3, 6, 0], 1},
    {[6, 4, 4, 2, 8, 8, 9, 0, 5, 5, 0, 4, 2, 7, 6, 8], 2},
    {[2, 3, 2, 1, 3, 8, 6, 1, 0, 4, 3, 0, 3, 8, 4, 5], 0},
    {[2, 3, 2, 6, 5, 0, 9, 4, 7, 1, 2, 7, 1, 4, 4, 8], 2},
    {[5, 2, 5, 1, 5, 8, 3, 3, 7, 9, 6, 4, 4, 3, 2, 2], 2},
    {[1, 7, 4, 8, 2, 7, 0, 4, 7, 6, 7, 5, 8, 2, 7, 6], 3},
    {[4, 8, 9, 5, 7, 2, 2, 6, 5, 2, 1, 9, 0, 3, 0, 6], 1},
    {[3, 0, 4, 1, 6, 3, 1, 1, 1, 7, 2, 2, 4, 6, 3, 5], 3},
    {[1, 8, 4, 1, 2, 3, 6, 4, 5, 4, 3, 2, 4, 5, 8, 9], 3},
    {[2, 6, 5, 9, 8, 6, 2, 6, 3, 7, 3, 1, 6, 8, 6, 7], 2}
  ]

  @cluster_size 5000
  @limit 1000

  def num2digits(num), do: n2d(num, [])
  defp n2d(0, acc), do: acc
  defp n2d(num, acc), do: n2d(div(num, 10), [rem(num, 10) | acc])

  def digits2num(list), do: d2n(list, 0)
  defp d2n([], acc), do: acc
  defp d2n([h | t], acc), do: d2n(t, acc * 10 + h)

  # 适应度
  def fitness(gene) do
    # 用基因与所有条件进行比较, 差异值越大表明适应度越低
    Enum.map(@filters, fn {x, b} -> abs(diff(gene, x, 0) - b) end)
    |> Enum.sum()
  end

  # 计算差异度
  defp diff([], [], acc), do: acc
  defp diff([h1 | t1], [h2 | t2], acc) when h1 == h2, do: diff(t1, t2, acc + 1)
  defp diff([_ | t1], [_ | t2], acc), do: diff(t1, t2, acc)

  # 自然选择, 适应度越高，有越大的可能能活下去
  def selection(cluster) do
    cluster
    |> Enum.map(fn x -> {x, fitness(x)} end)
    |> Enum.sort_by(fn {_, x} -> x end)
    |> Enum.take(5000)
    |> Enum.map(fn {x, _} -> x end)
    |> Enum.uniq()
  end

  # 种群繁衍下一代
  def multiply(cluster), do: mpy(cluster, [])

  defp mpy([], acc), do: acc
  defp mpy([_], acc), do: acc

  defp mpy([h1, h2 | t], acc) do
    # 随机生下若干个后代
    children =
      1..Enum.random(1..50)
      |> Enum.map(fn _ -> gene_exchange(h1, h2, []) end)

    mpy(t, children ++ acc)
  end

  # 基因交换
  defp gene_exchange([], [], acc), do: Enum.reverse(acc)

  defp gene_exchange([h1 | t1], [h2 | t2], acc) do
    # 有概率会基因突变
    new_gene =
      case :rand.uniform(10) do
        1 ->
          # 突变
          0..9
          |> Enum.filter(fn x -> x not in [h1, h2] end)
          |> Enum.random()

        _ ->
          Enum.random([h1, h2])
      end

    gene_exchange(t1, t2, [new_gene | acc])
  end

  # 初始族群
  def init_cluster() do
    1..@cluster_size
    |> Enum.map(fn _ -> gene_one(16) end)
  end

  defp gene_one(size) do
    res =
      2..size
      |> Enum.map(fn _ -> Enum.random(0..9) end)

    [Enum.random(1..9) | res]
  end

  # 代际更替
  def generation_iter(cluster, @limit),
    do:
      cluster
      |> Enum.map(fn x -> {x, fitness(x)} end)
      |> Enum.sort_by(fn {_, x} -> x end)
      |> Enum.take(1)

  def generation_iter(cluster, index) do
    next_cluster =
      selection(cluster)
      |> Enum.shuffle()
      |> multiply

    # 评估
    [{x, y}] =
      Enum.map(next_cluster, fn x -> {x, fitness(x)} end)
      |> Enum.sort_by(fn {_, x} -> x end)
      |> Enum.take(1)

    case y do
      0 ->
        [{x, y}]

      _ ->
        Logger.debug(
          "#{index}'s generation, cluster size #{Enum.count(next_cluster)}, best diff => #{y}, #{
            inspect(x)
          }"
        )

        generation_iter(next_cluster, index + 1)
    end
  end

  def test do
    cluster = init_cluster() |> multiply()

    [{x, y}] = generation_iter(cluster, 0)
    Logger.info("best diff => #{y}, res => #{digits2num(x)}")
  end
end
