defmodule Patricia.Node do
  defstruct(
    key: nil,
    value: nil,
    prefix: nil,
    mask: nil,
    left: nil,
    right: nil
  )
end
