function analysis_data( v_data, sampling_freq, playing, graph_name)
% Plot 2 graphs, time domain and frequecny domain
% Play the waveforms

if (isempty(playing))
    playing = false;
end

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
ylim([-120 max(amp)]);
xlabel('Frequency(Hz)');
ylabel('signal Amplitude (dB)');

if (strcmp(graph_name,'') == false)
  saveas (1, graph_name);
end

if (playing)
  sound(v_data,sampling_freq);
end

end
