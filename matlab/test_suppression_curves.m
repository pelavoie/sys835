%Suppression_curves

% split gain 0...1 in 50 equivalent values 
gain_m_vect = linspace(0.0,1.0,50);

% test : Plot curves on a graph
lookup_table = zeros(length(15),length(gain_m_vect));
hold on
for eps=1:15
  lookup_table(eps,:) = func_suppress_curve(eps,gain_m_vect);
  plot(convert_to_db(gain_m_vect),convert_to_db( func_suppress_curve(eps,gain_m_vect) ));
end
save test.dat lookup_table 
dlmwrite ("test2.dat", lookup_table, ",")
xlim([-10 0])
ylim([-30 0])
title('Courbes de suppression du bruit pour différents epsilon')
xlabel('Ratio g (dB)')
ylabel("Gain du canal(dB)")
hold off



