defmodule OddPeriodSquareRoots do
  @moduledoc """
  https://projecteuler.net/problem=64
  """
  require Logger
  require Integer
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
    # Logger.info(t)
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


  @doc """
  是否为完全平方数
  """
  def is_square(x), do: square?(x, 1)
  defp square?(x, index) when index * index > x, do: false
  defp square?(x, index) when index * index == x, do: true
  defp square?(x, index), do: square?(x, index + 1)

  def solution(limit), do: 1..limit |> Enum.filter(fn x -> not is_square(x) end) |> Enum.filter(fn x -> length(get_loop(x)) |> Integer.is_odd() end)

end
