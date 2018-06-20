defmodule DateTool do
  @moduledoc """
  日期工具
  """

  @doc """
  计算儒略日
  ## Example

  iex(1)> DateTool.calculate_julian_day(1977,3,27,12,0,0)
  2443230.0

  """
  def calculate_julian_day(year, month, day, hour, minute, second) do
    a = div(14 - month, 12)
    y = year + 4800 - a
    m = month + 12 * a - 3

    jdn = day + div(153 * m + 2, 5) + 365 * y + div(y, 4) - div(y, 100) + div(y, 400) + -32045.5
    jdn + hour / 24 + minute / 1440 + second / 86400
  end

  @doc """
  根据蔡勒公式算星期几
  ## Example

  iex> 

  """
  def zeller_week(year, month, day) do
    {year, m} =
      if month <= 2 do
        {year - 1, month + 12}
      else
	{year, month}
      end

    y = rem(year, 100)
    c = div(year, 100)
    w = rem(y + div(y, 4) + div(c, 4) - 2 * c + div(13 * (m + 1), 5) + day - 1, 7)

    if w < 0 do
      w + 7
    else
      w
    end
  end
end
