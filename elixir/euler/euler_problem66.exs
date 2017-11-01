defmodule DiophantineEquation do
  @moduledoc """
  https://projecteuler.net/problem=66
  """
  require Logger
  require Integer

  @doc """
  是否为完全平方数
  """
  def is_square(n), do: square(n, 1)
  defp square(n, index) when index * index > n, do: {false, 0}
  defp square(n, index) when index * index == n, do: {true, index}
  defp square(n, index), do: square(n, index + 1)

  @doc """
  获得开方的循环列表
  """
  def get_loop(x) do
    {n, m, z} = root_iter(1, x, nearest_root(x, 1))
    gl(x, n, z, [m], [{n, m, z}])
  end

  defp gl(x, n, z, acc, state) do
    {nn, nm, nz} = root_iter(n, x, z)
    cond do
      Enum.member?(state, {nn, nm, nz}) -> acc
      :else -> gl(x, nn, nz, [nm | acc], [{nn, nm, nz}|state])
    end
  end

  
  @spec root_iter(Integer, Integer, Integer) :: Tuple
  def root_iter(n, x, y) do
    # Logger.info("#{inspect {n, x, y}}")
    nn = div(x - y * y, n)
    {m, _, _, z} = iter(nn, x, y)
    # Logger.info("#{inspect {nn, m, z}}")
    # Logger.info("--------------------")
    {nn, m, z}
  end


  def get_t(x, n, y) do
    nr = nearest_root(x, 1)
    gett(nr, x, n, y, nr)
  end

  defp gett(0, _x, _n, _y, _nr), do: 0
  defp gett(t, x, n, y, nr) do
    o = (t + y) / n
    v = div(t + y, n)
    # Logger.info("#{inspect {o, v}}")
    cond do
      o == 0 -> gett(t-1, x, n, y, nr)
      o == v -> t
      :else -> gett(t-1, x, n, y, nr)
    end
  end


  def iter(n, x, y) do
    # Logger.info("#{inspect {n, x, y}}")
    t = get_t(x, n, y)
    cond do
      t == 0 -> {1, n, x, n - y}
      :else -> {div(y + t, n), n, x, t}
    end
  end


  @doc """
  非完全平方数，最接近这个数字的整数平方根, 步长为limit
  """
  @spec nearest_root(Integer, Integer) :: Integer
  def nearest_root(x, d), do: nr(x, 0, d)
  defp nr(x, index, d) when index * index > x, do: index - d
  defp nr(x, index, d), do: nr(x, index + d, d)

  defp citer(x, y, z), do: {y, x * y + z}
  defp cgent([], acc), do: acc
  defp cgent([h|t], {0, 0}), do: cgent(t, {1, h})
  defp cgent([h|t], {z, y}), do: cgent(t, citer(h, y, z))

  @doc """
  计算x开方的第k次收敛
  """
  def convergent(x, k), do: _convergent(x, k, get_loop(x), nearest_root(x, 1))
  defp _convergent(_x, k, loop, root) do
    d = div(k, length(loop))
    r = rem(k, length(loop))
    ba = List.duplicate(loop, d) |> List.flatten([root])
    cgent(Enum.slice(loop, 1..r) ++ ba, {0, 0})
  end



  def minimal_d(d), do: md(d, 1)
  defp md(d, index) do
    {x, y} = convergent(d, index)
    # Logger.info("#{inspect {x, y}}")
    cond do
      (y * y - x * x * d) == 1 -> {y, x}
      :else -> md(d, index + 1)
    end
  end


  def solution(limit) do
    1..limit
    |> Stream.filter(fn
      x -> {flag, _} = is_square(x)
      not flag
    end)
    |> Stream.map(fn x -> minimal_d(x) end)
    |> Stream.map(fn {x, _} -> x end)
    |> Enum.to_list() |> Enum.max()
  end

  
end
