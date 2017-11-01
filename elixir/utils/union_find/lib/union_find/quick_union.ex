defmodule UnionFind.QuickUnion do
  @moduledoc """
  unionfind中quickunion算法elixir实现
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
  def handle_call({:find, p}, _from, state), do: {:reply, find(state.id, p), state}
  def handle_call({:count}, _from, state), do: {:reply, state.count, state}
  def handle_cast({:union, p, q}, state) do
    with pid <- find(state.id, p),
	 qid <- find(state.id, q),
	   c <- state.count do
      cond do
      	pid == qid -> {:noreply, state}
      	:else -> {:noreply, %__MODULE__{state | id: Map.update(state.id, pid, qid, fn _ -> qid end), count: c - 1}}
      end
    end
  end

  defp find(id, p) do
    cond do
      Map.get(id, p) == p -> p
      :else -> find(id, Map.get(id, p))
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
