function v_suppression = func_suppress_curve(eps, v_parm)
  %Calculate the suppression factor 
  % from equation no.4
  % epsilon : arbitrary arguments
  % v_parm : vector of gain parameter values
  % v_suppression : vector of suppression values
  v_suppression=[];
  for i = 1:length(v_parm)
    I0 = calc_I0(eps, v_parm(i));
    if (I0 ~= Inf)
      fact = 1/2*(1+sqrt(v_parm(i)));
      numer = exp((-1)*eps) * I0;
      denom = 1+exp((-1)*eps) * I0;
      suppress_gain_m = fact * numer/denom;
    else
      suppress_gain_m = 1;
    end
     
    v_suppression = [v_suppression, suppress_gain_m];
  end
end