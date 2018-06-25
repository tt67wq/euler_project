defmodule Euler152 do
  @moduledoc """
  https://projecteuler.net/problem=152
  """
  require Logger

  @base 2..45
  @limit 1000

  def gene_print(gene), do: gp(gene, Enum.to_list(@base), [])

  defp gp([], _, acc), do: Enum.reverse(acc)

  defp gp([h | t], [h1 | t1], acc) do
    case h do
      1 -> gp(t, t1, [h1 | acc])
      0 -> gp(t, t1, acc)
    end
  end

  def gene_express(gene) do
    Enum.zip(@base, gene)
    |> Enum.filter(fn {_, x} -> x > 0 end)
    |> Enum.reduce(0, fn {x, _}, acc -> acc + 1 / (x * x) end)
  end

  def breed(gene) do
    1..10
    |> Enum.map(fn _ -> mutation(gene) end)
  end

  @doc """
  变异
  """
  def mutation(gene) do
    case rem(Enum.random(1..5), 5) do
      0 ->
        pos = Enum.random(@base)

        case Enum.at(gene, pos - 2) do
          1 -> List.replace_at(gene, pos, 0)
          0 -> List.replace_at(gene, pos, 1)
        end

      _ ->
        gene
    end
  end

  def nature_choose(genes) do
    genes
    |> Enum.map(fn x -> {x, gene_express(x)} end)
    |> Enum.sort_by(fn {_, x} -> abs(x - 0.5) end)
    |> Enum.take(@limit)
    |> Enum.map(fn {x, _} -> x end)
  end

  def iter(genes) do
    genes
    |> Enum.reduce([], fn x, acc -> breed(x) ++ acc end)
    |> nature_choose()
  end

  def solution() do
    init = List.duplicate(1, 44) |> List.duplicate(1000)

    sl(init, 0)
    |> Enum.uniq()
    |> Enum.map(fn x -> gene_print(x) end)
  end

  defp sl(genes, index) when index > 100, do: genes

  defp sl(genes, index) do
    Logger.info(index)
    sl(iter(genes), index + 1)
  end
end
