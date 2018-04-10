defmodule UnionFind.QuickFind do
  @moduledoc """
  unionfind中quickfind算法elixir实现
  """
  defstruct id: %{},
    count: 0

  @type uf :: %__MODULE__{}

  use GenServer

  def handle_call({:connected, p, q}, _from, state) do
    cond do
      Map.get(state.id, p) == nil -> {:reply, false, state}
      Map.get(state.id, q) == nil -> {:reply, false, state}
      :else -> {:reply, Map.get(state.id, p) == Map.get(state.id, q), state}
    end
  end

  def handle_call({:show}, _from, state), do: {:reply, state, state}
  def handle_call({:find, p}, _from, state), do: {:reply, Map.get(state.id, p), state}
  def handle_call({:count}, _from, state), do: {:reply, state.count, state}
  def handle_cast({:union, p, q}, state) do
    with pid <- Map.get(state.id, p),
	 qid <- Map.get(state.id, q),
	   c <- state.count do
      cond do
      	pid == qid -> {:noreply, state}
      	:else -> {:noreply, %__MODULE__{state | id: updateId(state.id, pid, qid), count: c - 1}}
      end
    end
  end

  def updateId(id, from, to), do: update(id, Map.keys(id), from, to)
  defp update(id, [], _from, _to), do: id
  defp update(id, [h|t], from, to) do
    cond do
      Map.get(id, h) == from -> update(Map.update(id, h, from, fn _x -> to end), t, from, to)
      :else -> update(id, t, from, to)
    end
  end

  # =====================

  def start_link(state \\ []), do: GenServer.start_link(__MODULE__, initialize(state), name: __MODULE__)

  @spec initialize(list) :: uf 
  def initialize(members) do
    %__MODULE__{
      id: [%{}|members] |> Enum.reduce(fn (x, acc) -> Map.update(acc, x, x, &(&1)) end),
      count: length(members)
    }
  end

  def connected(p, q), do: GenServer.call(__MODULE__, {:connected, p, q})
  def find(p), do: GenServer.call(__MODULE__, {:find, p})
  def union(p, q), do: GenServer.cast(__MODULE__, {:union, p, q})
  def count(), do: GenServer.call(__MODULE__, {:count})
  def show(), do: GenServer.call(__MODULE__, {:show})
end
