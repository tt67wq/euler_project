defmodule Rle do
  @moduledoc """
  RLE压缩算法
  """
  @type str :: String.t()

  # 压缩
  @spec encode(str) :: str
  def encode(string) do
    string
    |> String.codepoints()
    |> rle([])
    |> Enum.map(fn {chr, cnt} -> "#{cnt}#{chr}" end)
    |> Enum.join()
  end

  defp rle([], out), do: Enum.reverse(out)
  defp rle([x | src], [{x, c} | out]), do: rle(src, [{x, c + 1} | out])
  defp rle([x | src], out), do: rle(src, [{x, 1} | out])

  # 解压
  @spec decode(str) :: str
  def decode(string) do
    ~r/(\d+)([^\d])/
    |> Regex.scan(string)
    |> Enum.map(fn [_, cnt, chr] -> String.duplicate(chr, to_int(cnt)) end)
    |> Enum.join()
  end

  defp to_int(string), do: string |> Integer.parse() |> elem(0)
end
