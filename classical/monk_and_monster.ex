defmodule MonkAndMonster do
  @moduledoc """
  有三个和尚和三个妖怪要利用唯一的一条小船过河，这条小船一次只能载两个人，
  同时，无论是在河的两岸还是在船上，只要妖怪的数量大于和尚的数量，
  妖怪们就会将和尚吃掉。现在需要选择一种过河的安排，保证和尚和妖怪都能过河且和尚不能被妖怪吃掉。

  定义数据结构
  初始状态为
  [{:left, [3, 3]}, {:right, [0, 0]}, {:ship_pos, 0}]
  简化为 [3,3,0,0,0]
  """
  @doc """
  状态转换
  过河的情况无非5种
  1个和尚过河， 2个和尚过河
  1个妖怪过河， 2个妖怪过河
  1个和尚加一个妖怪过河
  过滤掉非法的状态机和和尚被吃掉的情况
  """
  def state_iter([lh, lm, rh, rm, 0]) do
    [
      [lh - 1, lm, rh + 1, rm, 1],
      [lh - 2, lm, rh + 2, rm, 1],
      [lh, lm - 1, rh, rm + 1, 1],
      [lh, lm - 2, rh, rm + 2, 1],
      [lh - 1, lm - 1, rh + 1, rm + 1, 1]
    ]
    |> Enum.filter(fn x -> not negetive?(x) end)
    |> Enum.filter(fn x -> safe?(x) end)
  end

  def state_iter([lh, lm, rh, rm, 1]) do
    [
      [lh + 1, lm, rh - 1, rm, 0],
      [lh + 2, lm, rh - 2, rm, 0],
      [lh, lm + 1, rh, rm - 1, 0],
      [lh, lm + 2, rh, rm - 2, 0],
      [lh + 1, lm + 1, rh - 1, rm - 1, 0]
    ]
    |> Enum.filter(fn x -> not negetive?(x) end)
    |> Enum.filter(fn x -> safe?(x) end)
  end

  defp negetive?([h | _t]) when h < 0, do: true
  defp negetive?([_h | t]), do: negetive?(t)
  defp negetive?([]), do: false

  defp over?([h | _t]), do: h == [0, 0, 3, 3, 1]

  @doc """
  是否全部结束
  """
  defp all_over?(chains) do
    l1 = length(chains)
    l2 = chains |> Enum.filter(fn x -> over?(x) end) |> length()
    l1 == l2
  end

  @doc """
  检查是否安全
  """
  def safe?([lh, lm, 0, _rm, _]), do: lh >= lm
  def safe?([0, _lm, rh, rm, _]), do: rh >= rm
  def safe?([lh, lm, rh, rm, _]), do: lh >= lm and rh >= rm

  @doc """
  防止循环
  """
  def repeat?(chain, state), do: rp(chain, state)
  defp rp([h | _t], state) when state == h, do: true
  defp rp([_h | t], state), do: rp(t, state)
  defp rp([], _state), do: false

  def state_chain([h | t] = chain) do
    state_iter(h)
    |> Enum.filter(fn x -> not repeat?(t, x) end)
    |> Enum.map(fn x -> [x | chain] end)
  end

  @doc """
  树结构展开为一个列表
  """
  def state_tree(chains), do: chains |> Enum.reduce([], fn x, acc -> state_chain(x) ++ acc end)

  def solution() do
    sl([[[3, 3, 0, 0, 0]]])
  end

  defp sl(chains) do
    cond do
      all_over?(chains) -> chains
      :else -> sl(state_tree(chains))
    end
  end
end
