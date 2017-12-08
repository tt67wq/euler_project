defmodule UnionFind do
  @moduledoc """
  unionfind算法elixir实现
  """
  defstruct id: %{},
    count: 0,
    sz: %{}

  @type uf :: %__MODULE__{}

  use GenServer
  require Logger

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
      	:else ->
	  {id, sz} = union(state.id, state.sz, pid, qid)
	  {:noreply, %__MODULE__{state | id: id, sz: sz, count: c - 1}}
      end
    end
  end

  defp find(id, p) do
    x = Map.get(id, p)
    cond do
      x == p -> p
      :else ->
	Map.update(id, p, Map.get(id, x), fn _ -> Map.get(id, x) end)
	find(id, Map.get(id, p))
    end
  end

  defp union(id, sz, pid, qid) do
    with pweight <- Map.get(sz, pid),
	 qweight <- Map.get(sz, qid) do
      cond do
	pweight < qweight ->
	  {Map.update(id, pid, qid, fn _ -> qid end), Map.update(sz, qid, nil, fn x -> x + pweight end)}
	:else ->
	  {Map.update(id, qid, pid, fn _ -> pid end), Map.update(sz, pid, nil, fn x -> x + qweight end)}
      end
    end
  end



  # =====================

  def start_link(state \\ []), do: GenServer.start_link(__MODULE__, initialize(state), name: __MODULE__)

  @spec initialize(list) :: uf 
  def initialize(members) do
    %__MODULE__{
      id: [%{}|members] |> Enum.reduce(fn (x, acc) -> Map.update(acc, x, x, &(&1)) end),
      count: length(members),
      sz: [%{}|members] |> Enum.reduce(fn (x, acc) -> Map.update(acc, x, 1, fn _ -> 1 end) end)
    }
  end

  def connected(p, q), do: GenServer.call(__MODULE__, {:connected, p, q})
  def find(p), do: GenServer.call(__MODULE__, {:find, p})
  def union(p, q), do: GenServer.cast(__MODULE__, {:union, p, q})
  def count(), do: GenServer.call(__MODULE__, {:count})
  def show(), do: GenServer.call(__MODULE__, {:show})
end
