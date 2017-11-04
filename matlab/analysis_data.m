function v_suppression = analysis_data( v_data, sampling_freq, play=false, graph_name='')
% Plot 2 graphs, time domain and frequecny domain
% Play the waveforms

subplot(2,1,1);
time_s= (1:length(v_data))*(1/sampling_freq);
amp = (v_data);
plot(time_s,amp);
xlim([0 time_s(length(time_s))]);
%ylim([min(amp) max(amp)]);
xlabel('time(sec)');
ylabel('signal Amplitude (V)');

subplot(2,1,2);
v_fft=fft(v_data);
N=length(v_data);
freq = (1:length(v_fft)) * (sampling_freq/N);
amp = convert_to_db(abs(v_fft)/(0.5*N));
plot(freq, amp);
xlim([0 sampling_freq/2]);
ylim([-90 max(amp)]);
xlabel('Frequency(Hz)');
ylabel('signal Amplitude (dB)');

if (!strcmp(graph_name,''))
  saveas (1, graph_name);
endif

if (play)
  sound(v_data,sampling_freq);
endif

endfunction
