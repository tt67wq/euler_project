defmodule Euler150 do
  @moduledoc """
  https://projecteuler.net/problem=150
  """
  require Logger
  @base1 1_048_576
  @base2 524_288

  # for k = 1 up to k = 500500: 
  #   t := (615949*t + 797807) modulo 220
  #   sk := t−219

  # Linear Congruential Generator
  def t(0), do: [0]
  def t(k), do: t(k, 0, [0])
  defp t(k, index, acc) when index > k, do: acc
  defp t(k, index, [h | _] = acc), do: t(k, index + 1, [rem(615_949 * h + 797_807, @base1) | acc])

  @doc """
  s(0)..s(k)
  """
  def s(k) do
    [_ | t] =
      t(k)
      |> Enum.reverse()
      |> Enum.map(fn x -> x - @base2 end)

    t
  end

  @doc """
  构建一个三角形
  """
  def build_triange(list), do: bt(list, 0, 1, %{})

  defp bt([], _, level, acc), do: Map.update(acc, level, [], fn x -> x |> Enum.reverse() end)

  defp bt([h | t] = list, index, level, acc) do
    # need new level?
    lm = div(level * (level + 1), 2)

    cond do
      index >= lm ->
        bt(list, index, level + 1, acc)

      :else ->
        case Map.fetch(acc, level) do
          :error ->
            # new level
            nacc = Map.update(acc, level - 1, [], fn x -> x |> Enum.reverse() end)
            bt(t, index + 1, level, Map.put(nacc, level, [h]))

          {:ok, l} ->
            bt(t, index + 1, level, Map.put(acc, level, [h | l]))
        end
    end
  end

  def min_from_root(tr, {level, offset} = root),
    do:
      mfr(
        tr,
        root,
        1,
        Map.fetch!(tr, level) |> Enum.at(offset),
        Map.fetch!(tr, level) |> Enum.at(offset)
      )

  defp mfr(tr, {level, offset} = root, index, bcc, acc) do
    case Map.fetch(tr, level + index) do
      :error ->
        acc

      {:ok, list} ->
        ts =
          Enum.slice(list, offset, index + 1)
          |> Enum.sum()

        bcc = bcc + ts

        if bcc > acc do
          mfr(tr, root, index + 1, bcc, acc)
        else
          mfr(tr, root, index + 1, bcc, bcc)
        end
    end
  end

  def solution() do
    # [15, -14, -7, 20, -13, -5, -3, 8, 23, -26, 1, -4, -5, -18, 5, -16, 31, 2, 9, 28, 3]
    s(500_500 - 1)
    |> build_triange()
    |> sl(1, 0, 0)
  end

  defp sl(_, level, _, acc) when level > 1000, do: acc

  defp sl(tr, level, offset, acc) do
    cond do
      offset >= level ->
        Logger.info("#{level}, #{acc}")
        sl(tr, level + 1, 0, acc)

      :else ->
        m = min_from_root(tr, {level, offset})

        cond do
          m < acc ->
            sl(tr, level, offset + 1, m)

          :else ->
            sl(tr, level, offset + 1, acc)
        end
    end
  end
end
