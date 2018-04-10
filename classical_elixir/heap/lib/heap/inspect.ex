defimpl Inspect, for: Heap do
  import Inspect.Algebra

  def inspect heap, opts do
    concat [
      "#Heap<",
      to_doc(Enum.to_list(heap), opts),
      ">"
    ]
  end
end
