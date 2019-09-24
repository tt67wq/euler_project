defmodule Euler45 do
  @moduledoc """
  https://projecteuler.net/problem=45
  """

  @spec triangle(Integer) :: Integer
  def triangle(n), do: div(n * (n + 1), 2)

  @spec pentagon(Integer) :: Integer
  def pentagon(n), do: div(n * (3 * n - 1), 2)

  @spec hexagon(Integer) :: Integer
  def hexagon(n), do: n * (2 * n - 1)

  defp now(), do: :os.system_time(:milli_seconds)

  @spec iter(list) :: list
  def iter(state) do
    {tp, {index, value}} = Enum.min_by(state, fn {_, {_, v}} -> v end)
    {_, {_, value2}} = Enum.max_by(state, fn {_, {_, v}} -> v end)

    cond do
      value == value2 ->
        state

      :else ->
        nstate =
          case tp do
            :t -> Keyword.put(state, :t, {index + 1, triangle(index + 1)})
            :p -> Keyword.put(state, :p, {index + 1, pentagon(index + 1)})
            :h -> Keyword.put(state, :h, {index + 1, hexagon(index + 1)})
          end

        iter(nstate)
    end
  end

  def run() do
    start = now()
    state = [{:t, {286, triangle(2)}}, {:p, {165, pentagon(1)}}, {:h, {143, hexagon(1)}}]
    res = iter(state)
    timeuse = now() - start
    IO.inspect(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
