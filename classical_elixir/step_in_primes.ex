defmodule StepPrimes do
  def step(g, m, n) do
    Stream.unfold({m, []}, fn {x, acc} ->
      cond do
        !acc || x >= n - g -> nil
        is_prime?(x) && is_prime?(x + g) -> {[x, x + g], {x + 1, nil}}
        true -> {acc, {x + 1, []}}
      end
    end)
    |> Enum.to_list()
    |> List.last()
  end

  defp is_prime?(n) when n in [2, 3], do: true

  defp is_prime?(n) do
    floored_sqrt =
      :math.sqrt(n)
      |> Float.floor()
      |> round

    !Enum.any?(2..floored_sqrt, &(rem(n, &1) == 0))
  end
end
