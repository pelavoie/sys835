% test of channel filters
% Based on McAulay and Malpass Speech Enhancement p.141
freq_sample=8000;
v_fc=[240 360 480 600 720 840 975 1125 1275 1425 1575 1750 1950 2150 2350 2600 2900 3200 3535];
v_bw=[120 120 120 120 120 120 150 150 150 150 150 200 200 200 300 300 300 300 370];

hold on
for i = 1:length(v_fc)
  [b,a] = calc_channel_filter(v_fc(i), v_bw(i), freq_sample);
  [h,w] = freqz(b,a,1024);
  plot(w/(2*pi)*freq_sample,convert_to_db(h));
end
xlim([0 4e3])
ylim([-50 0])
hold off