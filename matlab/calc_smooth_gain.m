function smoothed_gain = calc_smooth_gain(current_gain, last_gain)
  % Return a smoothed gain
  % According to eq.6
  if (current_gain >= last_gain)
    beta = 1;
  else
    beta=0.5;
  endif
    
  smoothed_gain = last_gain + beta*(current_gain - last_gain);
endfunction