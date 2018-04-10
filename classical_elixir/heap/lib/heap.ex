defmodule Heap do
  defstruct h: nil, n: 0, d: nil

  @moduledoc """
  A heap is a special tree data structure. Good for sorting and other magic.
  See also: [Heap (data structure) on Wikipedia](https://en.wikipedia.org/wiki/Heap_(data_structure)).
  """

  @type t :: %Heap{}

  @doc """
  Create an empty min heap.
  A min heap is a heap tree which always has the smallest value at the root.
  """
  @spec min() :: Heap.t()
  def min(), do: Heap.new(:>)

  @doc """
  Create an empty max heap.
  A max heap is a heap tree which always has the largest value at the root.
  """
  @spec max() :: Heap.t()
  def max(), do: Heap.new(:<)

  @doc """
  Create an empty heap.
  """
  @spec new() :: Heap.t()
  @spec new(:> | :<) :: Heap.t()
  def new(direction \\ :>), do: %Heap{d: direction}

  @doc """
  Test if the heap is empty.
  """
  @spec empty?(Heap.t()) :: boolean()
  def empty?(%Heap{h: nil, n: 0}), do: true
  def empty?(%Heap{}), do: false

  @doc """
  Test if the heap contains the element <elem>
  """
  @spec member?(Heap.t(), any()) :: boolean()
  def member?(%Heap{} = heap, value) do
    root = Heap.root(heap)
    heap = Heap.pop(heap)
    has_member?(heap, root, value)
  end

  @doc """
  Push a new element into the heap.
  """
  @spec push(Heap.t(), any()) :: Heap.t()
  def push(%Heap{h: h, n: n, d: d}, v), do: %Heap{h: meld(h, {v, []}, d), n: n + 1, d: d}

  @doc """
  Pop the root element off the heap and discard it.
  """
  @spec pop(Heap.t()) :: Heap.t()
  def pop(%Heap{h: nil, n: 0}), do: nil
  def pop(%Heap{h: {_, q}, n: n, d: d}), do: %Heap{h: pair(q, d), n: n - 1, d: d}

  @doc """
  Return the element at the root of the heap.
  """
  @spec root(Heap.t()) :: any()
  def root(%Heap{h: {v, _}}), do: v
  def root(%Heap{h: nil, n: 0}), do: nil

  @doc """
  Return the number of elements in the heap.
  """
  @spec size(Heap.t()) :: non_neg_integer()
  def size(%Heap{n: n}), do: n

  @doc """
  Quickly sort an enumerable with a heap.
  """
  @spec sort(Enum.t()) :: List.t()
  @spec sort(Enum.t(), :< | :>) :: List.t()
  def sort(enum, direction \\ :>) do
    enum
    |> Enum.into(Heap.new(direction))
    |> Enum.to_list()
  end

  defp meld(nil, queue, _), do: queue
  defp meld(queue, nil, _), do: queue

  defp meld({k0, l0}, {k1, _} = r, :>) when k0 < k1, do: {k0, [r | l0]}
  defp meld({_, _} = l, {k1, r0}, :>), do: {k1, [l | r0]}

  defp meld({k0, l0}, {k1, _} = r, :<) when k0 > k1, do: {k0, [r | l0]}
  defp meld({_, _} = l, {k1, r0}, :<), do: {k1, [l | r0]}

  defp pair([], _), do: nil
  defp pair([q], _), do: q

  defp pair([q0, q1 | q], d) do
    q2 = meld(q0, q1, d)
    meld(q2, pair(q, d), d)
  end

  defp has_member?(_, previous, compare) when previous == compare, do: true
  defp has_member?(nil, _, _), do: false

  defp has_member?(heap, _, compare) do
    previous = Heap.root(heap)
    heap = Heap.pop(heap)
    has_member?(heap, previous, compare)
  end
end
