%Suppression_curves

% split gain 0...1 in 50 equivalent values 
gain_m_vect = linspace(0.0,1.0,50);

% test : Plot curves on a graph
hold on
for eps=1:15
  plot(convert_to_db(gain_m_vect),convert_to_db( func_suppress_curve(eps,gain_m_vect) ));
end
xlim([-10 12])
ylim([-25 0])
hold off



