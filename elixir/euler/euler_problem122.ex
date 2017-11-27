defmodule EfficientExponentiation do
  @moduledoc """
  https://projecteuler.net/problem=122
  """
  use GenServer
  require Logger

  ### GenServer API
  def init(state), do: {:ok, state}

  def handle_call({:get, tag, key}, _from, state) do
    case Map.fetch(state, tag) do
      {:ok, mc} ->
	case Map.fetch(mc, key) do
	  {:ok, value} -> {:reply, value, state}
	  :error -> {:reply, nil, state}
	end
      :error -> {:reply, nil, state}
    end
  end

  def handle_cast({:set, tag, key, value}, state) do
    case Map.fetch(state, tag) do
      {:ok, mc} ->
	{:noreply, Map.update!(state, tag, fn _ -> Map.put(mc, key, value) end)}
      :error ->
	{:noreply, Map.put(state, tag, %{key => value})}
    end
  end

  def handle_cast({:drop, tag, keys}, state) do
    case Map.fetch(state, tag) do
      {:ok, mc} ->
	{:noreply, Map.update!(state, tag, fn _ -> Map.drop(mc, keys) end)}
      :error ->
	{:noreply, state}
    end
  end

  ### Client
  def start_link(state \\ %{}) do
    GenServer.start_link(__MODULE__, state, name: __MODULE__)
  end

  def get(tag, key), do: GenServer.call(__MODULE__, {:get, tag, key})
  def set(tag, key, value), do: GenServer.cast(__MODULE__, {:set, tag, key, value})
  def drop(tag, keys), do: GenServer.cast(__MODULE__, {:drop, tag, keys})
  def set_and_get(tag, key, value) do
    set(tag, key, value)
    value
  end

  def level(0), do: [{1, [1]}]
  def level(n) do
    bl = cache_level(n-1)
    level(bl, [])
  end

  def cache_level(n) do
    v = get(:level, n)
    case v do
      nil -> set_and_get(:level, n, level(n))
      _ -> v
    end

  end

  defp level([], acc), do: acc |> MapSet.new() |> MapSet.to_list() |> Enum.sort_by(fn {x, _} -> x end)
  defp level([{v, trace}|t], acc), do: level(t, ([v|trace] |> Enum.map(fn x -> {x + v, [x|trace]} end)) ++ acc)

  def solution() do
    start_link()
    sl(0, [], 0)
  end

  defp sl(_index, acc, bcc) when length(acc) == 200, do: bcc
  defp sl(index, acc, bcc) do
    ls = cache_level(index)
    first_apns = ls |> Enum.map(fn {x, _} -> x end)
    |> Enum.sort() |> Enum.dedup()
    |> Enum.filter(fn x -> not Enum.member?(acc, x) end)
    |> Enum.filter(fn x -> x <= 200 end)
    Logger.info("level: #{index}, new nums: #{inspect first_apns}, len: #{length(first_apns)}, bcc: #{bcc}")
    sl(index+1, acc++first_apns, bcc + index * length(first_apns))
  end


end
