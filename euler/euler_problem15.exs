defmodule LatticePaths do
  @moduledoc """
  Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.
  How many such routes are there through a 20×20 grid?
  """
  defstruct value: nil, left: nil, right: nil
  @type t :: %LatticePaths{}

  def tree(), do: %LatticePaths{}
  def tree(level), do: tree(level, 0, %LatticePaths{})
  defp tree(level, level, acc), do: acc
  defp tree(level, index, acc) do
    tree(level, index+1, grow(acc))
  end
  
  def grow(%LatticePaths{value: nil}), do: %LatticePaths{value: 0, left: 1, right: -1}
  def grow(%LatticePaths{left: left, right: right}=t), do: %LatticePaths{t | left: grow(left), right: grow(right)}
  def grow(number), do: %LatticePaths{value: number, left: number+1, right: number-1}

  @spec walk(t | integer) :: list
  def walk(number) when is_integer(number), do: [number]
  def walk(%LatticePaths{left: left, right: right}) do
    walk(left) ++ walk(right)
  end

  def count(n), do: tree(n) |> walk() |> Enum.filter(fn x -> x == 0 end) |> length()

end
