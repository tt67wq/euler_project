defmodule CocktailSortTest do
  use ExUnit.Case, async: true
  use ExCheck
  doctest CocktailSort

  test "sort" do
    lst = [1,3,2,67,23,54,12,63,62,123,42]
    assert CocktailSort.sort(lst) == Enum.sort(lst)
  end

end
