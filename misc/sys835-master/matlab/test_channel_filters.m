% test of channel filters
clf();
freq_sample=8000;
%fc=[240 360 480 600 720 840 975 1125 1275 1425 1575 1750 1950 2150 2350 2600 2900 3200 3535];
%bw=[120 120 120 120 120 120 150 150 150 150 150 200 200 200 300 300 300 300 370];

fc=[120 240 360 480 600 720 840 960 1100 1250 1400 1550 1700 1900 2100 2300 2600 2900 3200 3500];
bw=[120 120 120 120 120 120 120 150 150 150 150 150 200 200 200 300 300 300 300 350];
bw = bw*2;
hold on
for i = 1:length(v_fc)
  [b,a] = calc_channel_filter(fc(i), bw(i), freq_sample);
  [h,w] = freqz(b,a,1024);
  plot(w/(2*pi)*freq_sample,convert_to_db(h));
end
xlim([0 4e3])
ylim([-50 0])
hold off