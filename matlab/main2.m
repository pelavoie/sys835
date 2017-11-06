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
voice_threshold = 0.16;
eps = 10;
frame_sec = 20e-3;
samples_per_frame = frame_sec/(1/fs);

Result = [];
ch_noise_last = zeros(1,nb_channels);
ch_gain_smooth_last= zeros(1,nb_channels);
start_sample = 1;
while((start_sample + samples_per_frame) <= length(data))
  
  % process frames of frame_sec
  frame_data = data(start_sample:(start_sample + samples_per_frame - 1));
  frame_result = zeros(length(frame_data),1);
  
  %Noise Detector
  frame_energy = sumsq(frame_data);
  frame_is_noise = !detect_voice(frame_energy, voice_threshold);
  
  for n = 1:nb_channels
    % Separate signal into Channels (Channel Pre-filter)
    ch_data = filter(ch_parms_b(n,:), ch_parms_a(n,:), frame_data);
    
    % Compute Energy and noise
    ch_energy = sumsq(ch_data);
    ch_noise = ch_noise_last(n) + alpha*(ch_energy - ch_noise_last(n));
    
    ch_meas_parms = calc_meas_parm(ch_energy,ch_noise);
    ch_gain = func_suppress_curve(eps, ch_meas_parms);
    ch_gain_smoothed = calc_smooth_gain(ch_gain, ch_gain_smooth_last(n));
        
    %if Only Noise Frame, Apply gain on channel frame data.
    if frame_is_noise
        ch_data = ch_data * (ch_gain_smoothed);
    endif
    
    ch_gain_smooth_last(n) = ch_gain_smoothed;
    ch_noise_last(n) = ch_noise;
    
    % Recombine all Channel Data(180° outphased)
    if ((-1)^(n+1) > 0)
      frame_result += ch_data;
    else 
      frame_result -= ch_data;
    endif
    
  end
  Result = [Result; frame_result];
	start_sample = start_sample + samples_per_frame;
end

%Result
result_name = strcat('result_thr',num2str(voice_threshold),'_eps',num2str(eps),'_a',num2str(alpha));
analysis_data(Result, fs, true, strcat(result_name,'.png'));
audiowrite(strcat(result_name,'.wav'),Result,fs);