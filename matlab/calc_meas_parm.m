function meas_parm = calc_meas_parm(Vn2, noise)
  % Calculate measurement parameter from noise and Signal value
  % from equation no.3
  meas_parm = (Vn2 - noise)/vn2;
endfunction