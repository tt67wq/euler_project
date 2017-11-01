defmodule MaximumPath do
  @moduledoc """
  https://projecteuler.net/problem=67
  """
  require Logger
  defstruct value: nil, left: nil, right: nil
  @type t :: %MaximumPath{}

  def max_path(number) when is_integer(number), do: number
  def max_path(nil), do: 0
  def max_path([x]), do: x
  def max_path(%MaximumPath{value: value, left: left, right: right}), do: value + max(max_path(left), max_path(right))

  def generate_triangle(lines), do: gt(lines, [])
  defp gt([], acc), do: acc
  defp gt([h|t], []), do: gt(t, h)
  defp gt([h|t], acc) do
    Logger.info("完成了一行, 还剩下#{length([h|t])}行")
    Logger.info("#{inspect h}")
    a = make_triangle(h, acc, [])
    Logger.info("acc is #{inspect a}")
    nacc = a |> Enum.map(fn x -> max_path(x) end)
    Logger.info("max acc is #{inspect nacc}")
    gt(t, nacc |> Enum.reverse())
  end

  defp make_triangle([], _, acc), do: acc
  defp make_triangle([h|t1], [h1, h2 | t2], acc), do: make_triangle(t1, [h2 | t2], [%MaximumPath{value: h, left: h1, right: h2} | acc])

  def read_data_from_file(path) do
    {:ok, content} = File.read(path)
    content
  end

  def string2int(lst), do: lst |> Enum.map(fn x -> String.to_integer(x) end)

  def solution() do
    read_data_from_file("p067_triangle.txt")
    |> String.split("\n")
    |> Enum.map(fn x -> String.split(x) end)
    |> Enum.map(fn x -> string2int(x) end)
    |> Enum.reverse()
    |> generate_triangle()
    |> max_path()
  end


end
