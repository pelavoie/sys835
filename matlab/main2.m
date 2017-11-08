% Main
clear
[data,fs]=audioread('car.wav');
analysis_data(data,fs,false,'original.png');

% filters bank 
% Based on McAulay and Malpass Speech Enhancement p.141
%fc=[240 360 480 600 720 840 975 1125 1275 1425 1575 1750 1950 2150 2350 2600 2900 3200 3535];
%bw=[120 120 120 120 120 120 150 150 150 150 150 200 200 200 300 300 300 300 370];

% Bark Scale
fc=[60 150 250 350 450 570 700 840 1000 1170 1370 1600 1850 2150 2500 2900 3400];
bw=[80 100 100 100 110 120 140 150 160 190 210 240 280 320 380 450 550];

nb_channels=length(fc);
% Pre-Allocate variables
Result = zeros(length(data),1);

% Pre-calculate prefilters parms.
ch_parms_b= zeros(length(nb_channels),1);
ch_parms_a= zeros(length(nb_channels),1);

for n = 1:nb_channels
  [b,a] = calc_channel_filter(fc(n),bw(n),fs);
  ch_parms_b(n) =  b;
  ch_parms_a(n) =  a;
end

% Parameters
alpha = 0.4;
eps = 5;
frame_sec = 20e-3;
samples_per_frame = frame_sec/(1/fs);


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
  frame_energy = sumsq(frame_data_20ms*intmax('uint8'));
  % frame_is_noise = !detect_voice(frame_energy, voice_threshold);
  voice_threshold = noisedetector(frame_energy);
  frame_is_noise = frame_energy<=voice_threshold;

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
        end

        % Détermination du gain 
        ch_meas_parms = (ch_energy - ch_noise)/ch_energy;
        ch_gain = func_suppress_curve(eps, ch_meas_parms);

        % Application du gain
        ch_gain_smoothed = calc_smooth_gain(ch_gain, ch_gain_smooth_last(n));
        ch_data = ch_data * (ch_gain_smoothed);

        % Recombinaison signaux des canaux 
        % avec un déphasage de 180° entre eux.
        if (mod(n,2))
          frame_result = frame_result + ch_data;
        else 
          frame_result = frame_result - ch_data;
        end

        % Memorize last values
        ch_gain_smooth_last(n) = ch_gain_smoothed;
        ch_noise_last(n) = ch_noise;
    end
    
    Result(start_sample:(start_sample + samples_per_frame - 1)) = frame_result;
    start_sample = start_sample + samples_per_frame;
end

%Result
result_name = strcat('result_thr',num2str(voice_threshold),'_eps',num2str(eps),'_a',num2str(alpha));
audiowrite(strcat(result_name,'.wav'),Result,fs);
analysis_data(Result, fs, false, strcat(result_name,'.png'));