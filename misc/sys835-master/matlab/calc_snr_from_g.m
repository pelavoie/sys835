function snr = calc_snr_from_g(gain_m)
  % Calculate measurement parameter from noise and Signal value
  % from equation no.3
  snr = -1*ones(1,length(gain_m))./(gain_m-1);
end