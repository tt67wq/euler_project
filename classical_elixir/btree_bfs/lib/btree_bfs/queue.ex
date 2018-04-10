defmodule BtreeBfs.Queue do
  @moduledoc """
  队列的elixir实现
  """

  def insert(queue, nil), do: queue
  def insert(queue, item), do: :queue.in(item, queue)

  def insert_last(queue, nil), do: queue
  def insert_last(queue, item), do: :queue.in_r(item, queue)

  def member?(queue, item), do: :queue.member(item, queue)

  def filter(queue, fun), do: :queue.filter(fun, queue)

  def split(queue, n) do
    length = BtreeBfs.Queue.length(queue)

    if length >= n do
      :queue.split(n, queue)
    else
      :queue.split(length, queue)
    end
  end

  def take(queue, n) do
    {q1, _} = split(queue, n)
    q1
  end

  def pop(queue) do
    case :queue.out(queue) do
      {{:value, item}, new_queue} -> {item, new_queue}
      {:empty, new_queue} -> {nil, new_queue}
    end
  end

  def pop_last(queue) do
    case :queue.out_r(queue) do
      {{:value, item}, new_queue} -> {item, new_queue}
      {:empty, new_queue} -> {nil, new_queue}
    end
  end

  def first(queue) do
    unless is_empty?(queue) do
      :queue.get(queue)
    end
  end

  def last(queue) do
    unless is_empty?(queue) do
      :queue.get_r(queue)
    end
  end

  def head(queue) do
    unless is_empty?(queue) do
      :queue.head(queue)
    end
  end

  def tail(queue) do
    if is_empty?(queue) do
      queue
    else
      :queue.tail(queue)
    end
  end

  def drop(queue) do
    if is_empty?(queue) do
      queue
    else
      :queue.drop(queue)
    end
  end

  def drop_last(queue) do
    if is_empty?(queue) do
      queue
    else
      :queue.drop_r(queue)
    end
  end

  defdelegate length(queue), to: :queue, as: :len
  defdelegate from_list(queue), to: :queue
  defdelegate to_list(queue), to: :queue
  defdelegate is_empty?(queue), to: :queue, as: :is_empty
  defdelegate is_queue?(queue), to: :queue, as: :is_queue
  defdelegate join(queue1, queue2), to: :queue
  defdelegate reverse(queue), to: :queue
  defdelegate new(), to: :queue
end
