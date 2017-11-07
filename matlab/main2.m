% Main
[data,fs]=audioread("car.wav");
analysis_data(data,fs,false,'original.png');

% filters bank 
% Based on McAulay and Malpass Speech Enhancement p.141
%fc=[240 360 480 600 720 840 975 1125 1275 1425 1575 1750 1950 2150 2350 2600 2900 3200 3535];
%bw=[120 120 120 120 120 120 150 150 150 150 150 200 200 200 300 300 300 300 370];
%bw = bw*2
% Custom shop
fc=[120 240 360 480 600 720 840 960 1100 1250 1400 1550 1700 1900 2100 2300 2600 2900 3200 3500];
bw=[120 120 120 120 120 120 120 150 150 150 150 150 200 200 200 300 300 300 300 350];
bw = bw*2;

nb_channels=length(fc);

% Pre-calculate prefilters parms.
ch_parms_b= [];
ch_parms_a= [];
for n = 1:nb_channels
  [b,a] = calc_channel_filter(fc(n),bw(n),fs);
  ch_parms_b = [ch_parms_b; b];
  ch_parms_a = [ch_parms_a; a];
end

% Parameters
alpha = 0.4;
% voice_threshold = 0.16;
eps = 10;
frame_sec = 20e-3;
samples_per_frame = frame_sec/(1/fs);

Result = [];
ch_noise_last = zeros(1,nb_channels);
ch_gain_smooth_last= zeros(1,nb_channels);
ch_noise_1s= zeros(nb_channels, 50);
ch_avg_energy_1s = zeros(nb_channels, 1);
start_sample = 1;

while((start_sample + samples_per_frame) <= length(data))
  
  % process frames of 20ms
  frame_data_20ms = data(start_sample:(start_sample + samples_per_frame - 1));
  frame_result = zeros(length(frame_data_20ms),1);
  
  %Noise Detector
  frame_energy = bitshift(sumsq(frame_data_20ms*intmax('int16')),-16);
  % frame_is_noise = !detect_voice(frame_energy, voice_threshold);
  voice_threshold = noisedetector(frame_energy)
  frame_is_noise = frame_energy<=voice_threshold
  
  
  
  for n = 1:nb_channels
    % Separate signal into Channels (Channel Pre-filter)
    ch_data = filter(ch_parms_b(n,:), ch_parms_a(n,:), frame_data_20ms);
    
    % Compute Energy 
    ch_energy = sumsq(ch_data);
    
    if frame_is_noise
      % Compute Noise with smoothing (1 sec. noise frames)
      ch_noise_1s(n,:) = [ch_noise_1s(n,2:50) ch_energy];
      ch_avg_energy_1s(n) = sum(ch_noise_1s(n,:))/length(ch_noise_1s(n,:));
      ch_noise = ch_noise_last(n) + alpha*(ch_avg_energy_1s(n,:) - ch_noise_last(n));
    else
      % Compute Noise
      ch_noise = ch_noise_last(n) + alpha*(ch_energy - ch_noise_last(n));
    endif
            
    % Calculate Gain
    ch_meas_parms = calc_meas_parm(ch_energy,ch_noise);
    ch_gain = func_suppress_curve(eps, ch_meas_parms);
    
    % Smooth Gain with previous
    ch_gain_smoothed = calc_smooth_gain(ch_gain, ch_gain_smooth_last(n));
    
    % Apply gain is Frame is noise
    %if frame_is_noise
      ch_data = ch_data * (ch_gain_smoothed);
    %endif
    
    % Recombine all Channel Data(180° outphased)
    if ((-1)^(n+1) > 0)
      frame_result += ch_data;
    else 
      frame_result -= ch_data;
    endif
    
    % Memorize last values
    ch_gain_smooth_last(n) = ch_gain_smoothed;
    ch_noise_last(n) = ch_noise;
    
  end
  Result = [Result; frame_result];
	start_sample = start_sample + samples_per_frame;
end

%Result
result_name = strcat('result_thr',num2str(voice_threshold),'_eps',num2str(eps),'_a',num2str(alpha));
audiowrite(strcat(result_name,'.wav'),Result,fs);
analysis_data(Result, fs, true, strcat(result_name,'.png'));