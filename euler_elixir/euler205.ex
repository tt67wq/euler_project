defmodule Euler205 do
  @moduledoc false

  def peter_roll() do
    dice = 1..4

    for a0 <- dice,
        a1 <- dice,
        a2 <- dice,
        a3 <- dice,
        a4 <- dice,
        a5 <- dice,
        a6 <- dice,
        a7 <- dice,
        a8 <- dice do
      Enum.sum([a0, a1, a2, a3, a4, a5, a6, a7, a8])
    end
    |> Enum.reduce(%{}, fn x, acc -> Map.update(acc, x, 1, fn y -> y + 1 end) end)
  end

  def colin_roll() do
    dice = 1..6

    for a0 <- dice,
        a1 <- dice,
        a2 <- dice,
        a3 <- dice,
        a4 <- dice,
        a5 <- dice do
      Enum.sum([a0, a1, a2, a3, a4, a5])
    end
    |> Enum.reduce(%{}, fn x, acc -> Map.update(acc, x, 1, fn y -> y + 1 end) end)
  end

  def run do
    peter_total = 262_144
    colin_total = 46656
    pc = peter_roll() |> Map.to_list()
    cr = colin_roll() |> Map.to_list()

    pc
    |> Enum.map(fn {t, c} -> {{t, c}, Enum.filter(cr, fn {x, _} -> x < t end)} end)
    |> Enum.map(fn {x, y} -> {x, Enum.map(y, fn {_, z} -> z end)} end)
    |> Enum.map(fn {{_, x}, y} -> {x, Enum.sum(y)} end)
    |> Enum.map(fn {x, y} -> x / peter_total * y / colin_total end)
    |> Enum.sum()
  end
end
