function result = calc_I0(eps, gain_m)
  %Calculate the value of I0 
  % from equation no.5
  if (gain_m < 1)
    parms_I0 = 2*sqrt((eps/(1-gain_m)));
    fun = @(teta) exp(parms_I0*cos(teta));
    result = 1/(2*pi)*quad(fun,0,2*pi);
  else
    result = Inf;
  end 
endfunction