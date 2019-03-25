defmodule LinkNode do
  defstruct value: nil, next: nil
end

defmodule ReverseLinkList do
  @moduledoc """
  链表的逆转
  """

  def init do
    1..5
    |> Enum.map(fn x -> %LinkNode{value: x, next: nil} end)
    |> Enum.reduce(%LinkNode{}, fn x, acc -> Map.put(x, :next, acc) end)
  end

  def print_ll(%LinkNode{value: nil}), do: IO.puts(" ")
  def print_ll(ll) do
    IO.puts("#{ll.value}")
    print_ll(ll.next)
  end


  def reverse(ll), do: rev(ll, %LinkNode{})
  defp rev(%LinkNode{value: nil}, acc), do: acc
  defp rev(ll, acc) do
    nacc = %LinkNode{value: ll.value, next: acc}
    rev(ll.next, nacc)
  end
end
