defimpl Enumerable, for: Heap do

  def count heap do
    {:ok, Heap.size heap}
  end

  def member? heap, v do
    {:ok, Heap.member?(heap, v)}
  end

  def reduce(_,    {:halt,    acc}, _fun), do: {:halted, acc}
  def reduce(heap, {:suspend, acc},  fun), do: {:suspended, acc, &reduce(heap, &1, fun)}
  def reduce(heap, {:cont,    acc},  fun) do
    case Heap.root heap do
      nil ->
        {:done, acc}
      root ->
        heap = Heap.pop heap
        reduce(heap, fun.(root, acc), fun)
    end
  end

end
