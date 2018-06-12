defmodule SkipListTest do
  use ExUnit.Case
  doctest SkipList

  # test "greets the world" do
  #   assert SkipList.hello() == :world
  # end

  test "skip list search" do
    sl =
      0..18
      |> Enum.reduce(SkipList.new_sl(), fn x, acc -> SkipList.insert(acc, x, x * x) end)
    expect = 18 * 18
    assert SkipList.search(sl, 18).value == expect
  end
end
