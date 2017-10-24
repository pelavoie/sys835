%Suppression_curves
eps=5
% split gain 0...1 in 50 equivalent values 
gain_m_vect = linspace(0.0,1.0,50);

gain_v = suppress_curve(eps,gain_m_vect);
suppress_db = 10*log(gain_v)

function result = calc_I0(eps, gain_m)
  %Calculate the value of I0 according to (eq.5)
  parms_I0 = 2*sqrt((eps/(1-gain_m)));
  fun = @(teta) exp(parms_I0*cos(teta));
  result = 1/(2*pi)*quad(fun,0,2*pi);
end

function v_sup_gain = suppress_curve(eps, gain_m_vect)
  %Calculate the suppression factor from curves according to eq.4
  v_sup_gain=[];
  for i = 1:length(gain_m_vect)
    I0 = calc_I0(eps, gain_m_vect(i));
    fact = 1/2*(1+sqrt(gain_m_vect(i)));
    numer = exp((-1)*eps) * I0;
    denom = 1*exp((-1)*eps) * I0;
    suppress_gain_m = fact * numer/denom;
    
    %TODO: check denominator != 0
    if !(suppress_gain_m > 0 & suppress_gain_m < 1)
      suppress_gain_m = 1
     end
     
    v_sup_gain = [v_sup_gain, suppress_gain_m];
  end
end


function v_gain_db = v_convert_db(v_gain)
  %Converting to dB
  v_gain_db=[];
  for i = 1:length(v_gain)     
    v_sup_gain = [v_sup_gain, 10*log(v_gain)];
  end
end

