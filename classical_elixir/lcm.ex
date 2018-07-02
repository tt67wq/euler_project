defmodule LCM do
  @type int :: non_neg_integer
  @type ints :: [non_neg_integer]

  require Integer

  @spec lcm(int, int) :: int
  def lcm(a, b), do: div(a * b, Integer.gcd(a, b))

  @spec lcm_list(ints) :: int
  def lcm_list(list), do: lcl(list, 1)
  defp lcl([], acc), do: acc
  defp lcl([h | t], acc), do: lcl(t, lcm(h, acc))
end
