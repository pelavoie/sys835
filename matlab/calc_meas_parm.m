function meas_parm = calc_meas_parm(energy, noise)
  % Calculate measurement parameter from noise and Signal value
  % According to equation no.3
  meas_parm = (energy - noise)/energy;
endfunction