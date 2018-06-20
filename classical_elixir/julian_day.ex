defmodule JulianDay do
  @moduledoc """
  公历转换成儒略日
  """

  def calculate_julian_day(year, month, day, hour, minute, second) do
    a = div(14 - month, 12)
    y = year + 4800 - a
    m = month + 12 * a - 3

    jdn = day + div(153 * m + 2, 5) + 365 * y + div(y, 4) - div(y, 100) + div(y, 400) + -32045.5
    jdn + hour / 24 + minute / 1440 + second / 86400
  end
end
