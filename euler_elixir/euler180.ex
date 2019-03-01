defmodule Euler180 do
  @moduledoc """
  条件化简后 即为 x^n + y^n = z^n
  a / b 共有组合383个
  """

  require Integer

  @top 35

  def all, do: all(1, 2, [])

  defp all(1, b, acc) when b > @top, do: acc
  defp all(a, b, acc) when a == b, do: all(1, b + 1, acc)

  # defp all(a, b, acc), do: all(a + 1, b, [{a, b} | acc])
  defp all(a, b, acc) do
    cond do
      Integer.gcd(a, b) > 1 -> all(a + 1, b, acc)
      :else -> all(a + 1, b, [{a, b} | acc])
    end
  end

  def pow(_, 0), do: 1
  def pow(x, n) when Integer.is_odd(n), do: x * pow(x, n - 1)

  def pow(x, n) do
    result = pow(x, div(n, 2))
    result * result
  end

  # 分数相加
  def add({a1, b1}, {a2, b2}) do
    m = a1 * b2 + b1 * a2
    n = b1 * b2
    g = Integer.gcd(m, n)
    {div(m, g), div(n, g)}
  end

  # 分数乘方
  def frac_pow(m, n) when n < 0 do
    {a, b} = frac_pow(m, -n)
    {b, a}
  end

  def frac_pow({a, b}, n) do
    g = Integer.gcd(a, b)
    {pow(div(a, g), n), pow(div(b, g), n)}
  end

  # def test(n) do
  #   candidates = all()
  #   calculate(candidates, n)
  # end

  defp calculate(candidates, n) do
    r = Enum.map(candidates, fn x -> frac_pow(x, n) end)
    mp = Enum.reduce(candidates, %{}, fn x, acc -> Map.put(acc, frac_pow(x, n), x) end)

    for x <- candidates,
        y <- candidates do
      {x, y, add(frac_pow(x, n), frac_pow(y, n))}
    end
    |> Enum.filter(fn {_, _, z} -> Enum.member?(r, z) end)
    |> Enum.map(fn {x, y, z} -> {x, y, Map.get(mp, z)} end)
  end

  def run() do
    candidates = all()

    (calculate(candidates, 1) ++
       calculate(candidates, -1) ++ calculate(candidates, 2) ++ calculate(candidates, -2))
    |> Enum.uniq()
    |> Enum.map(fn {x, y, z} -> add(x, y) |> add(z) end)
    |> Enum.reduce({0, 1}, fn x, acc -> add(x, acc) end)
  end
end
