defmodule MonopolyOdds do
  @moduledoc """
  https://projecteuler.net/problem=84
  题目就看了半个钟头，我日
  """
  require Logger

  @community_chest ["Advance to Go", "Go to JAIL", nil, nil,nil,nil,nil,nil,nil,nil,nil,nil,nil,nil,nil,nil]
  @chance ["Advance to Go", "Go to JAIL", "Go to C1", "Go to E3", "Go to H2", "Go to R1", "Go to next R", "Go to next R", "Go to next U", "Go back 3 squares", nil, nil, nil, nil, nil, nil]

  @dice [1,2,3,4]

  def rand_throw(dice), do: dice |> Enum.random()
  def get_card(list) do
    [h|t] = list
    {h, t ++ [h]}
  end



  def state_update(state, location), do: state |> Map.update!(location, fn x -> x + 1 end)
  # def consecutive_doubles?([a, b, c]), do: a == b and b == c
  def path_add(location, step), do: (location + step) |> rem(40)
  def path_sub(location, step) do
    new_location = location - step
    cond do
      new_location < 0 -> 40 + new_location
      :else -> new_location
    end
  end

  defp gnr(location) do
    case location |> member?([5, 15, 25, 35]) do
      true -> location
      false -> gnr(location |> path_add(1))
    end
  end

  defp gnu(location) do
    case location |> member?([12, 28]) do
      true -> location
      false -> gnu(location |> path_add(1))
    end
  end

  def member?(elem, list), do: Enum.member?(list, elem)

  defp move(_location, count, _history, state, limit, _, _) when limit == count, do: state
  defp move(location, count, [h1, h2]=history, state, limit, cc_card, ch_card) do
    step1 = @dice |> rand_throw()
    step2 = @dice |> rand_throw()
    step = step1 + step2
    case step1 == step2 do
      true ->
	case {h1, h2} do
	  {true, true} ->
	    new_history = [true, true]
	    move(10, count + 1, new_history, state_update(state, 10), limit, cc_card, ch_card)
	  _ ->
	    new_history = [true, h1]
	    new_location = path_add(location, step)
	    case new_location == 30 do
	      true -> move(10, count+1, new_history, state_update(state, 10), limit, cc_card, ch_card)
	      false ->
		case new_location |> member?([2, 17, 33]) do
		  true ->
		    {cc, new_cc} = get_card(cc_card)
		    case cc do
		      "Advance to Go" -> move(0, count+1, new_history, state_update(state, 0), limit, new_cc, ch_card)
		      "Go to JAIL" -> move(10, count+1, new_history, state_update(state, 10), limit, new_cc, ch_card)
		      nil -> move(new_location, count+1, new_history, state_update(state, new_location), limit, new_cc, ch_card)
		    end
		  false ->
		    case new_location |> member?([7, 22, 36]) do
		      true ->
			{ch, new_ch} = get_card(ch_card)
			case ch do
			  nil -> move(new_location, count+1, new_history, state_update(state, new_location), limit, cc_card, new_ch)
			  "Advance to Go" -> move(0, count+1, new_history, state_update(state, 0), limit, cc_card, new_ch)
			  "Go to JAIL" -> move(10, count+1, new_history, state_update(state, 10), limit, cc_card, new_ch)
			  "Go to C1" -> move(11, count+1, new_history, state_update(state, 11), limit, cc_card, new_ch)
			  "Go to E3" -> move(24, count+1, new_history, state_update(state, 24), limit, cc_card, new_ch)
			  "Go to H2" -> move(39, count+1, new_history, state_update(state, 39), limit, cc_card, new_ch)
			  "Go to R1" -> move(5, count+1, new_history, state_update(state, 5), limit, cc_card, new_ch)
			  "Go to next R" ->
			    n = gnr(new_location)
			    move(n, count+1, new_history, state_update(state, n), limit, cc_card, new_ch)
			  "Go to next U" ->
			    n = gnu(new_location)
			    move(n, count+1, new_history, state_update(state, n), limit, cc_card, new_ch)
			  "Go back 3 squares" ->
			    n = path_sub(new_location, 3)
			    case new_location == 30 do
			      true -> move(10, count+1, new_history, state_update(state, 10), limit, cc_card, new_ch)
			      false ->
				case n |> member?([2, 17, 33]) do
				  true ->
				    {cc, new_cc} = get_card(cc_card)
				    case cc do
				      "Advance to Go" -> move(0, count+1, new_history, state_update(state, 0), limit, new_cc, new_ch)
				      "Go to JAIL" -> move(10, count+1, new_history, state_update(state, 10), limit, new_cc, new_ch)
				      nil -> move(n, count+1, new_history, state_update(state, new_location), limit, new_cc, new_ch)
				    end
				  false -> move(n, count+1, new_history, state_update(state, n), limit, cc_card, new_ch)
				end
			    end
			end
		      false -> move(new_location, count+1, new_history, state_update(state, new_location), limit, cc_card, ch_card)
		    end
		end
	    end
	end
      false ->
	new_history = [false, h1]
	new_location = path_add(location, step)
	case new_location == 30 do
	  true -> move(10, count+1, new_history, state_update(state, 10), limit, cc_card, ch_card)
	  false ->
	    case new_location |> member?([2, 17, 33]) do
	      true ->
		{cc, new_cc} = get_card(cc_card)
		case cc do
		  "Advance to Go" -> move(0, count+1, new_history, state_update(state, 0), limit, new_cc, ch_card)
		  "Go to JAIL" -> move(10, count+1, new_history, state_update(state, 10), limit, new_cc, ch_card)
		  nil -> move(new_location, count+1, new_history, state_update(state, new_location), limit, new_cc, ch_card)
		end
	      false ->
		case new_location |> member?([7, 22, 36]) do
		  true ->
		    {ch, new_ch} = get_card(ch_card)
		    case ch do
		      nil -> move(new_location, count+1, new_history, state_update(state, new_location), limit, cc_card, new_ch)
		      "Advance to Go" -> move(0, count+1, new_history, state_update(state, 0), limit, cc_card, new_ch)
		      "Go to JAIL" -> move(10, count+1, new_history, state_update(state, 10), limit, cc_card, new_ch)
		      "Go to C1" -> move(11, count+1, new_history, state_update(state, 11), limit, cc_card, new_ch)
		      "Go to E3" -> move(24, count+1, new_history, state_update(state, 24), limit, cc_card, new_ch)
		      "Go to H2" -> move(39, count+1, new_history, state_update(state, 39), limit, cc_card, new_ch)
		      "Go to R1" -> move(5, count+1, new_history, state_update(state, 5), limit, cc_card, new_ch)
		      "Go to next R" ->
			n = gnr(new_location)
			move(n, count+1, new_history, state_update(state, n), limit, cc_card, new_ch)
		      "Go to next U" ->
			n = gnu(new_location)
			move(n, count+1, new_history, state_update(state, n), limit, cc_card, new_ch)
		      "Go back 3 squares" ->
			n = path_sub(new_location, 3)
			case new_location == 30 do
			  true -> move(10, count+1, new_history, state_update(state, 10), limit, cc_card, new_ch)
			  false ->
			    case n |> member?([2, 17, 33]) do
			      true ->
				{cc, new_cc} = get_card(cc_card)
				case cc do
				  "Advance to Go" -> move(0, count+1, new_history, state_update(state, 0), limit, new_cc, new_ch)
				  "Go to JAIL" -> move(10, count+1, new_history, state_update(state, 10), limit, new_cc, new_ch)
				  nil -> move(n, count+1, new_history, state_update(state, new_location), limit, new_cc, new_ch)
				end
			      false -> move(n, count+1, new_history, state_update(state, n), limit, cc_card, new_ch)
			    end
			end
		    end
		  false -> move(new_location, count+1, new_history, state_update(state, new_location), limit, cc_card, ch_card)
		end
	    end
	end
    end
  end

  def get_weight(state, limit) do
    0..39 |> Enum.reduce(state, fn x, acc -> Map.update!(acc, x, fn x -> x / limit end) end)
  end


  def solution() do
    limit = 1000000
    state = 0..39 |> Enum.reduce(%{}, fn x, acc -> Map.update(acc, x, 0, &(&1)) end)
    new_state = move(0, 0, [-10, -10], state, limit, @community_chest, @chance) |> get_weight(limit)
    Enum.zip(new_state |> Map.keys(), new_state |> Map.values())
    |> Enum.sort_by(fn {_, x} -> x end)
    |> Enum.reverse()
  end

  
end
