clear
[x,fs]=audioread('car.wav');
% reshape signal data with a column for each 160 samples (20 ms)
samples=reshape(x,160,[]);
% allocate output signal matrix
nsamples =  length(samples(:,:));
cnt=0;
for s= 1:length(samples(:,:))
	xs = samples(:,s);
	frame_energy = sumsq(xs*intmax('uint8'));	
    voice_threshold = noisedetector(frame_energy);
    frame_is_noise = frame_energy<=voice_threshold;
	if (frame_is_noise)
		cnt++;
	end
end
