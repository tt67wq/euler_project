defmodule Euler166 do
  @moduledoc """
  https://projecteuler.net/problem=166
  """
  require Logger

  # 是否为同一元素序列
  defp equal_seq?([]), do: true
  defp equal_seq?([_]), do: true

  defp equal_seq?([h | t]) do
    case Enum.find(t, fn x -> x != h end) do
      nil -> true
      _ -> false
    end
  end

  # 获取行
  def take_rows(grid), do: trow(Enum.with_index(grid), 0, [])
  defp trow(_, 4, acc), do: acc

  defp trow(grid, index, acc) do
    bcc =
      grid
      |> Enum.filter(fn {_x, i} -> div(i, 4) == index end)
      |> Enum.map(fn {x, _} -> x end)

    trow(grid, index + 1, [bcc | acc])
  end

  # 获取列
  def take_columns(grid), do: tcol(Enum.with_index(grid), 0, [])

  defp tcol(_, 4, acc), do: acc

  defp tcol(grid, index, acc) do
    bcc =
      grid
      |> Enum.filter(fn {_x, i} -> rem(i, 4) == index end)
      |> Enum.map(fn {x, _} -> x end)

    tcol(grid, index + 1, [bcc | acc])
  end

  # 获取对角线
  def take_diagonal(grid) do
    grid_with_index = Enum.with_index(grid)

    d1 =
      grid_with_index
      |> Enum.filter(fn {_, i} -> rem(i, 3) == 0 and rem(i, 5) != 0 end)
      |> Enum.map(fn {x, _} -> x end)

    d2 =
      grid_with_index
      |> Enum.filter(fn {_, i} -> rem(i, 5) == 0 end)
      |> Enum.map(fn {x, _} -> x end)

    [d1, d2]
  end

  ## 检查方阵是否满足条件 BEGIN
  defp check(grid, 16) do
    # check row
    rs =
      take_rows(grid)
      |> Enum.map(fn x -> Enum.sum(x) end)

    row_pass = equal_seq?(rs)

    cond do
      row_pass ->
        # check column
        cs =
          take_columns(grid)
          |> Enum.map(fn x -> Enum.sum(x) end)

        col_pass = equal_seq?([List.first(rs) | cs])

        cond do
          col_pass ->
            # check diagonal
            ds =
              take_diagonal(grid)
              |> Enum.map(fn x -> Enum.sum(x) end)

            equal_seq?([List.first(rs) | ds])

          :else ->
            false
        end

      :else ->
        false
    end
  end

  defp check(grid, l) when l > 13 do
    rs =
      Enum.take(grid, 4)
      |> Enum.sum()

    # check column
    cs =
      take_columns(grid)
      |> Enum.filter(fn x -> Enum.count(x) == 4 end)
      |> Enum.map(fn x -> Enum.sum(x) end)

    col_pass = equal_seq?([rs | cs])

    cond do
      col_pass ->
        true

      :else ->
        false
    end
  end

  defp check(grid, 13) do
    rs =
      Enum.take(grid, 4)
      |> Enum.sum()

    # check column
    cs =
      take_columns(grid)
      |> Enum.filter(fn x -> Enum.count(x) == 4 end)
      |> Enum.map(fn x -> Enum.sum(x) end)

    col_pass = equal_seq?([rs | cs])

    cond do
      col_pass ->
        # check diagonal
        [d1, _] = take_diagonal(grid)

        cond do
          Enum.sum(d1) == rs -> true
          :else -> false
        end

      :else ->
        false
    end
  end

  defp check(grid, l) when l == 8 or l == 12 do
    # check row
    take_rows(grid)
    |> Enum.map(fn x -> Enum.sum(x) end)
    |> equal_seq?()
  end

  defp check(_, _), do: true

  ## 检查方阵是否满足条件 END

  defp bfs(pid, 16, acc), do: send(pid, {:ok, acc})

  defp bfs(pid, deep, acc) do
    Logger.info("#{inspect(acc)}")

    0..9
    |> Enum.map(fn x -> [x | acc] end)
    |> Enum.filter(fn x -> check(Enum.reverse(x), deep + 1) end)
    |> Enum.each(fn x -> bfs(pid, deep + 1, x) end)
  end

  def loop_accept(acc) do
    receive do
      {:ok, res} ->
        Logger.info("#{inspect(res)}")
        loop_accept([res | acc])

      {:finish, pid} ->
        send(pid, {:ok, acc})
    end
  end

  def run() do
    {:ok, pid} = Task.start(fn -> loop_accept([]) end)
    bfs(pid, 0, [])
    send(pid, {:finish, self()})

    receive do
      {:ok, res} ->
        Process.exit(pid, :kill)
        Enum.count(res)
    end
  end
end
