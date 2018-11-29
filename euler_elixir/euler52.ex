defmodule Euler52 do
  @moduledoc """
  http://pe-cn.github.io/52/
  """
  require Logger

  def num2list(n), do: n2l(n, [])
  defp n2l(0, acc), do: acc
  defp n2l(n, acc), do: n2l(div(n, 10), [rem(n, 10) | acc])

  @doc """
  数字x乘以n之后数字组成是否不变
  """
  def satisfy?(x, m) do
    a = Enum.sort(num2list(x))
    b = Enum.sort(num2list(x * m))
    a == b
  end

  defp iter(index, 7), do: index

  defp iter(index, m) do
    # Logger.info(index)

    cond do
      satisfy?(index, m) ->
        iter(index, m + 1)

      :else ->
        iter(index + 1, 2)
    end
  end

  def now(), do: :os.system_time(:milli_seconds)

  def run() do
    start = now()
    res = iter(125_874, 2)

    timeuse = now() - start
    IO.inspect(res)
    IO.puts("timeuse => #{timeuse} milliseconds")
  end
end
