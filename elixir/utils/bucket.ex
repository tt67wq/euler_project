defmodule Buckets do
  @moduledoc """
  将n个元素丢进m个桶里面，m个桶最终每个桶里的个数集合
  x1+x2+...+xm = n
  {x1, x2, .... xn}个数
  """
  def bucket(0, _), do: 1
  def bucket(_, 1), do: 1
  def bucket(n, m), do: bucket(n, 0, m, 0)
  defp bucket(n, k, _m, acc) when k > n, do: acc
  defp bucket(n, k, m, acc), do: bucket(n, k+1, m, bucket(n-k, m-1) + acc)
end
