defmodule LineHash do
  @moduledoc """
  线性散列
  """

  use GenServer
  require Logger

  def start_link(opts) do
    GenServer.start_link(__MODULE__, :ok, opts)
  end

  def put(server, n), do: GenServer.cast(server, {:put, n})
  def locate(server, n), do: GenServer.call(server, {:locate, n})
  def overview(server), do: GenServer.call(server, {:overview})

  #### callback

  def init(:ok) do
    {:ok, %{h0: 2, h1: 4, cursor: 0, count: 2, size: 5, buckets: %{0 => {[], []}, 1 => {[], []}}}}
  end

  def handle_call({:overview}, _, state), do: {:reply, state, state}

  def handle_call({:locate, n}, _, state) do
    res =
      if rem(n, state.h0) < state.cursor do
        # 已分裂
        {rem(n, state.h1), Map.get(state.buckets, rem(n, state.h1))}
      else
        # 未分裂
        {rem(n, state.h0), Map.get(state.buckets, rem(n, state.h0))}
      end

    {:reply, res, state}
  end

  def handle_cast({:put, n}, state) do
    index =
      if rem(n, state.h0) < state.cursor do
        rem(n, state.h1)
      else
        rem(n, state.h0)
      end

    {main, overflow} = Map.get(state.buckets, index)

    cond do
      Enum.count(main) >= state.size ->
        Logger.info("触发分裂")
        # 触发分裂
        new_buckets =
          state.buckets
          |> Map.put(index, {main, [n | overflow]})
          |> bucket_split(state.h1, state.cursor)

        new_state =
          if state.cursor + 1 == state.count do
            # 触发轮换
            %{
              h0: state.h1,
              h1: state.h1 * 2,
              cursor: 0,
              count: buckets_size(new_buckets),
              size: 5,
              buckets: new_buckets
            }
          else
            state
            |> Map.put(:buckets, new_buckets)
            |> Map.put(:cursor, state.cursor + 1)
          end

        {:noreply, new_state}

      :else ->
        new_buckets = Map.put(state.buckets, index, {[n | main], overflow})
        {:noreply, Map.put(state, :buckets, new_buckets)}
    end
  end

  # 分裂
  defp bucket_split(buckets, h1, cursor) do
    {{main, overflow}, temp} = Map.pop(buckets, cursor)
    all = main ++ overflow

    # 按照h1 hash
    all
    |> Enum.map(fn x -> {rem(x, h1), x} end)
    |> Enum.reduce(temp, fn {index, x}, acc ->
      Map.update(acc, index, {[x], []}, fn {y, o} -> {[x | y], o} end)
    end)
  end

  defp buckets_size(buckets), do: buckets |> Map.to_list() |> Enum.count()
end
