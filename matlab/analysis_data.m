function v_suppression = analysis_data( v_data, sampling_freq, play=false)
% Plot 2 graphs, time domain and frequecny domain
% Play the waveforms

subplot(2,1,1);
sec= (1:length(v_data))*(1/sampling_freq);
plot(sec,v_data);
xlim([0 sec(length(sec))]);
ylim([min(v_data) max(v_data)]);
xlabel('time(sec)');
ylabel('signal Amplitude');

subplot(2,1,2);
v_fft=fft(v_data);
N=length(v_data);
freq = (1:length(v_fft)) * (sampling_freq/N);
plot(freq, abs(v_fft));
xlim([0 sampling_freq/2]);
%ylim([min(v_data) max(v_data)]);
xlabel('Frequency(Hz)');
ylabel('signal Amplitude');

if (play)
  sound(v_data,sampling_freq);
endif
endfunction
