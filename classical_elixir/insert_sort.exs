defmodule InsertSort do
  def sort(list), do: _sort(list, [])

  def half(list) do
    [
      left: Enum.slice(list, 0..(div(length(list), 2) - 1)),
      right: Enum.slice(list, div(length(list), 2)..-1),
      povit: Enum.at(list, div(length(list), 2))
    ]
  end

  def insert(value, []) do
    [value]
  end

  def insert(value, [povit]) when value > povit do
    [povit, value]
  end

  def insert(value, [povit]) do
    [value, povit]
  end

  def insert(value, list) do
    [left: left, right: right, povit: povit] = half(list)
    _insert(value, left, right, povit)
  end

  defp _insert(value, left, [povit], povit) when value > povit do
    left ++ [povit, value]
  end

  defp _insert(value, left, [povit], povit) do
    left ++ [value, povit]
  end

  defp _insert(value, left, right, povit) when value > povit do
    left ++ insert(value, right)
  end

  defp _insert(value, left, right, _povit) do
    insert(value, left) ++ right
  end

  defp _sort([], acc), do: acc

  defp _sort([head | tail], acc) do
    _sort(tail, insert(head, acc))
  end
end

list = [12, 43, 61, 21, 32, 123, 23, 3, 56]
# list = [1,2,4]

IO.inspect(InsertSort.sort(list))
