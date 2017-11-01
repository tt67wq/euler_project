defmodule PrimeTest do
  use ExUnit.Case
  doctest Prime

  test "greets the world" do
    assert Prime.hello() == :world
  end
end
