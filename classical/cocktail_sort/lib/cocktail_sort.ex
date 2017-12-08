defmodule CocktailSort do

  @moduledoc """
  鸡尾酒排序是冒泡排序的轻微变形。不同的地方在于，鸡尾酒排序是从低到高然后从高到低来回排序，而冒泡排序则仅从低到高去比较序列里的每个元素。
  他可比冒泡排序的效率稍微好一点，原因是冒泡排序只从一个方向进行比对(由低到高)，每次循环只移动一个项目。
  排序过程：
  先对数组从左到右进行冒泡排序（升序），则最大的元素去到最右端
  再对数组从右到左进行冒泡排序（降序），则最小的元素去到最左端
  以此类推，依次改变冒泡的方向，并不断缩小未排序元素的范围，直到最后一个元素结束
  """
  require List
  @empty []

  @doc """
  ## Examples

      iex> CocktailSort.sort([23, 12, 45, 56, 17])
      [12, 17, 23, 45, 56]
  """
  @spec sort(list) :: list
  def sort(l), do: sort(l, [], [], :>)
  def sort(@empty, left, right, _), do: left ++ right
  def sort(l, left, right, :>) do
    x = pop(l, :>)
    sort(List.delete(l, x), left, [x|right], :>)
  end
  def sort(l, left, right, :<) do
    x = pop(l, :<)
    sort(List.delete(l, x), left ++ [x], right, :<)
  end

  defp pop([a], _), do: a
  defp pop([a|[b|tail]], :>) do
    cond do
      a > b ->
        pop([a|tail], :>)
      true ->
        pop([b|tail], :>)
    end
  end
  defp pop([a|[b|tail]], :<) do
    cond do
      a < b ->
        pop([a|tail], :<)
      true ->
        pop([b|tail], :<)
    end
  end
end
