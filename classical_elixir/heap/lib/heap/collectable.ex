defimpl Collectable, for: Heap do

  def into heap do
    {heap, fn
      (h, {:cont, v}) -> Heap.push h, v
      (h, :done)      -> h
      (_, :halt)      -> :ok
    end}
  end

end
