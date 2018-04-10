defmodule Patricia.Helper do

  use Bitwise
  
  defmacro zero(x, mask) do
    quote do: (unquote(x) &&& (unquote(mask) >>> 1)) == 0
  end

  defmacro match(key, mask, prefix) do
    quote do: (unquote(key) &&& bnot(unquote(mask) - 1)) == unquote(prefix)
  end

end
