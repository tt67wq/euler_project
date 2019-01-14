defmodule PortDemo do
  @moduledoc """
  test port lib
  """
  def run() do
    port = Port.open({:spawn, "cat"}, [:binary])
    send(port, {self(), {:command, "world"}})

    receive do
      {^port, {:data, result}} ->
        IO.puts("Elixir got: #{inspect(result)}")
    end
  end
end
