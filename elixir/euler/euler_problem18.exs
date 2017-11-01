defmodule MaximumPath do
  @moduledoc """
  By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

     3
    7 4
   2 4 6
  8 5 9 3

  That is, 3 + 7 + 4 + 9 = 23.

  Find the maximum total from top to bottom of the triangle below:
  
		75
	       95 64
	      17 47 82
	     18 35 87 10
	    20 04 82 47 65
	   19 01 23 75 03 34
	  88 02 77 73 07 63 67
	 99 65 04 28 06 16 70 92
	41 41 26 56 83 40 80 70 33
       41 48 72 33 47 32 37 16 94 29
      53 71 44 65 25 43 91 52 97 51 14
     70 11 33 28 77 73 17 78 39 68 17 57
    91 71 52 38 17 14 91 43 58 50 27 29 48
   63 66 04 68 89 53 67 30 73 16 69 87 40 31
  04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
  """
  require String
  defstruct value: nil, left: nil, right: nil

  @type t :: %MaximumPath{}
  
  def max_path(number) when is_integer(number), do: number
  def max_path(str_number) when Kernel.is_bitstring(str_number), do: String.to_integer(str_number)
  def max_path(%MaximumPath{value: value, left: left, right: right}) do
    String.to_integer(value) + max(max_path(left), max_path(right))
  end

  @spec pair(list, list) :: list
  def pair(line1, line2), do: pair(line1, line2, [])
  defp pair([_h], _, acc), do: Enum.reverse(acc)
  defp pair([h1, h2 | t1], [h3 | t2], acc), do: pair([h2 | t1], t2, [%MaximumPath{value: h3, left: h1, right: h2} | acc])

  @spec generate_triangle(list, list) :: list
  def generate_triangle(line, tl), do: generate_triangle(line, tl, [])
  defp generate_triangle([], _, acc), do: Enum.reverse(acc)
  defp generate_triangle([h1 | t1], [h2, h3 | t2], acc) do
    generate_triangle(t1, [h3 | t2], [%MaximumPath{value: h1, left: h2, right: h3} | acc])
  end

  def line_to_list(line), do: String.split(line, " ")
end
