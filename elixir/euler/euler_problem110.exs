defmodule DiophantineReciprocalsII do
  @moduledoc """
  https://projecteuler.net/problem=110
  分式 1a+1b=1n 的个数 就是(1+d(n2))/2，其中d(n)是n的约数的个数
  d(n2)=N=∏(2pi+1)
  """

  @limit 4000000
  @primes [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47]
  
  require Logger

  def d(plist), do: d(plist, 1)
  defp d([], acc), do: (acc + 1) |> div(2)
  defp d([{_, 0}|t], acc), do: d(t, acc)
  defp d([{_, p}|t], acc), do: d(t, (2 * p + 1) * acc)

  def get_n(gene), do: Enum.zip(@primes, gene) |> d()
  def survive?(gene) do
    nums = get_n(gene)
    cond do
      nums > @limit -> true
      :else -> false
    end
  end
  
  def generate_gene(), do: 0..5 |> Enum.to_list |> Enum.random
  def generate_genes(), do: 0..14 |> Enum.map(fn _ -> generate_gene() end) |> Enum.sort_by(fn x -> -x end)
  def new_population(), do: 1..1000 |> Enum.map(fn _ -> generate_genes() end)

  def next_generation(f, m), do: 1..8 |> Enum.map(fn _ -> breed(f, m) end)
  def breed(f, m), do: bd(f, m, [])
  def bd([], [], acc), do: acc |> Enum.sort_by(fn x -> -x end) |> variation |> variation
  def bd([hf|tf], [hm|tm], acc) do
    cond do
      hf == hm -> bd(tf, tm, [hf|acc])
      :else -> bd(tf, tm, [[hf, hm]|>Enum.random()|acc])
    end
  end

  defp variation(gene), do: gene |> List.replace_at(0..14 |> Enum.random(), generate_gene())

  def population_iter(population) do
    np = pi(population, [])
    np |> Enum.filter(fn x -> x |> survive?() end)
    |> Enum.sort_by(fn x -> x |> get_n() end)
    |> Enum.take(4000)
    |> Enum.sort_by(fn x -> x |> get_num() end)
    |> Enum.take(1000)
  end
  defp pi([], acc), do: acc
  defp pi([_], acc), do: acc
  defp pi([h1, h2|t], acc), do: pi(t, next_generation(h1, h2) ++ acc)

  def pow(a, b), do: :math.pow(a, b) |> round()
  def get_num(gene), do: Enum.zip(@primes, gene) |> Enum.reduce(1, fn {a, b}, acc -> pow(a, b) * acc end)

  def solution() do
    population = 1..100 |> Enum.reduce(new_population(), fn _, acc -> population_iter(acc) end)
    population |> Enum.map(fn x -> {x, x |> get_n(), get_num(x)} end)
  end
end
