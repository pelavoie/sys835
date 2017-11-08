% test of channel filters
clf();
freq_sample=8000;
v_fc=[60 150 250 350 450 570 700 840 1000 1170 1370 1600 1850 2150 2500 2900 3400];
v_bw=[80 100 100 100 110 120 140 150 160 190 210 240 280 320 380 450 550];

hold on
for i = 1:length(v_fc)
  [b,a] = calc_channel_filter(fc(i), bw(i), freq_sample);
  [h,w] = freqz(b,a,1024);
  plot(w/(2*pi)*freq_sample,convert_to_db(h));
end
xlim([0 4e3])
ylim([-50 0])
title('Filtres de séparation des différents canaux')
xlabel('Fréquence (Hz)')
ylabel("Gain(dB)")
hold off