defmodule Euler185 do
  @moduledoc """
  尝试退火算法
  """

  require Logger

  @t0 50000.0
  @t1 1.0e-8
  @k 0.98
  @l 1000
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

  def num2digits(num), do: n2d(num, [])
  defp n2d(0, acc), do: acc
  defp n2d(num, acc), do: n2d(div(num, 10), [rem(num, 10) | acc])

  def digits2num(list), do: d2n(list, 0)
  defp d2n([], acc), do: acc
  defp d2n([h | t], acc), do: d2n(t, acc * 10 + h)

  def distance(list) do
    Enum.map(@filters, fn {x, b} ->
      a = diff(list, x, 0)
      abs(a - b)
    end)
    |> Enum.sum()
  end

  # 计算差异
  defp diff([], [], acc), do: acc
  defp diff([h1 | t1], [h2 | t2], acc) when h1 == h2, do: diff(t1, t2, acc + 1)
  defp diff([_ | t1], [_ | t2], acc), do: diff(t1, t2, acc)

  # 退火
  def sa(t, _, _, _, acc) when t < @t1, do: acc

  def sa(t, @l, last_d, same_time, acc) do
    current_d = distance(acc)
    Logger.debug("退火一次, #{inspect(acc)}, #{current_d}, 当前温度#{t}")

    cond do
      current_d == 0 ->
        # 结束
        acc

      last_d == current_d and same_time > 100 ->
        # 重来
        Logger.debug("重来！")
        sa(@t0, 0, 100, 0, gene_one(16))

      last_d == current_d ->
        sa(t * @k, 0, current_d, same_time + 1, acc)

      :else ->
        # 正常退火
        sa(t * @k, 0, current_d, 0, acc)
    end
  end

  def sa(t, index, last_d, same_time, acc) do
    # 产生一个新的解析
    bcc = gene_new(acc, [])
    df = distance(bcc) - distance(acc)

    cond do
      df <= 0 ->
        if :math.exp(df / t) >= :rand.uniform() do
          sa(t, index + 1, last_d, same_time, bcc)
        else
          sa(t, index + 1, last_d, same_time, acc)
        end

      df < 0 ->
        sa(t, index + 1, last_d, same_time, bcc)

      :else ->
        sa(t, index + 1, last_d, same_time, acc)
    end
  end

  defp gene_new([], acc), do: Enum.reverse(acc)

  defp gene_new([h | t], acc) do
    case Enum.random(0..2) do
      0 -> gene_new(t, [Enum.random(0..9) | acc])
      _ -> gene_new(t, [h | acc])
    end
  end

  defp gene_one(size) do
    res =
      2..size
      |> Enum.map(fn _ -> Enum.random(0..9) end)

    [Enum.random(1..9) | res]
  end

  def run do
    sa(@t0, 0, 100, 0, gene_one(16))
    |> digits2num
  end
end
