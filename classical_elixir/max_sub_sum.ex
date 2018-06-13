defmodule MaxSubSum do
  @moduledoc """
  连续子数组的最大和
  """

  def max_sub(list), do: mss(list, 0, 0)

  defp mss([], _bcc, acc), do: acc

  defp mss([h | t], bcc, acc) do
    nacc =
      if bcc + h > acc do
        bcc + h
      else
        acc
      end

    if bcc + h < 0 do
      mss(t, 0, nacc)
    else
      mss(t, bcc + h, nacc)
    end
  end
end
