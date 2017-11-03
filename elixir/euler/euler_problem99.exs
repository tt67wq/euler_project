defmodule LargestExponential do
  @moduledoc """
  https://projecteuler.net/problem=99
  """
  require Logger
  require Time

  def solution() do
    st = Time.utc_now()
    {_, content} = File.read("p099_base_exp.txt")
    {line, _} = content |> String.split("\n")
    |> Enum.map(fn x -> x |> String.split(",") end)
    |> Enum.map(fn x -> x |> string2int() end)
    |> Enum.map(fn [a, b] -> get_log(a, b)  end)
    |> find_max_index()
    et = Time.utc_now()
    Logger.info("solution: #{line+1}, time cost: #{Time.diff(et, st, :microsecond)}ms")
  end
  defp string2int(lst), do: lst |> Enum.map(fn x -> String.to_integer(x) end)

  def get_log(a, b), do: b * :math.log(a)

  def find_max_index(list), do: fmi(list, 0, 0, 0)
  defp fmi([], acc, _, m), do: {m, acc}
  defp fmi([h|t], acc, index, _m) when h > acc, do: fmi(t, h, index+1, index)
  defp fmi([_|t], acc, index, m), do: fmi(t, acc, index+1, m)
  
end
