defmodule RleTest do
  use ExUnit.Case
  doctest Rle

  # test "greets the world" do
  #   assert Rle.hello() == :world
  # end

  test "encode" do
    origin = "aaaabbbccdeffg"
    expected = "4a3b2c1d1e2f1g"
    assert Rle.encode(origin) == expected
  end

  test "decode" do
    origin = "4a3b2c1d1e2f1g"
    expected = "aaaabbbccdeffg"
    assert Rle.decode(origin) == expected
  end
end
