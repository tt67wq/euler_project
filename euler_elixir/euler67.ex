defmodule Euler67 do
  @moduledoc """
  https://projecteuler.net/problem=67
  """
  @limit 99

  def read_data_from_file(path) do
    {:ok, content} = File.read(path)
    content
  end

  defp string2int(list), do: Enum.map(list, fn x -> String.to_integer(x) end)

  def with_index(list), do: wi(list, 0, %{})
  defp wi([], _, acc), do: acc
  defp wi([h | t], index, acc), do: wi(t, index + 1, Map.put(acc, index, h))

  def get_datas() do
    read_data_from_file("p067_triangle.txt")
    |> String.split("\n")
    |> Enum.map(fn x -> String.split(x) end)
    |> Enum.map(fn x -> string2int(x) end)
    |> Enum.map(fn x -> with_index(x) end)
    |> with_index()
  end

  def bfs(tr, @limit, j) do
    Map.get(tr, @limit)
    |> Map.get(j)
  end

  def bfs(tr, i, j) do
    n =
      Map.get(tr, i)
      |> Map.get(j)

    case :ets.lookup(:euler67, {i, j}) do
      [{_, value}] ->
        value

      [] ->
        lm = bfs(tr, i + 1, j)
        rm = bfs(tr, i + 1, j + 1)
        v = max(lm, rm) + n
        :ets.insert(:euler67, {{i, j}, v})
        v
    end
  end

  @spec now() :: integer()
  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    :ets.new(:euler67, [:named_table])

    res =
      get_datas()
      |> bfs(0, 0)

    IO.puts(res)
    IO.puts("timeuse => #{now() - start} milliseconds")
  end
end
