% Main
% 20 ms frame (160 samples @ 8kHz)c=1
ranges = zeros(128,1);
cumulative = zeros(128,1);
[x,fs]=audioread("car.wav",'native')
% filter bank 
%fc=[240 360 480 600 720 840 975 1125 1275 1425 1575 1750 1950 2150 2350 2600 2900 3200 3535]
%bw=[120 120 120 120 120 120 150 150 150 150 150 200 200 200 300 300 300 300 370]
fc=[60 150 250 350 450 570 700 840 1000 1170 1370 1600 1850 2150 2500 2900 3400];
bw=[80 100 100 100 110 120 140 150 160 190 210 240 280 320 380 450 550];
ts=125e-6;
fn=fs/2;
% generate coefficients for filter bank
for c= 1:length(fc)
	b2 = bw(c)/2;
	fmin = fc(c)-b2;
	fmax = fc(c)+b2;
	[b, a] = butter(2, [fmin fmax]/fn);
	coeffs(:,:,c) = [b ; a];
end
% reshape signal data with a column for each 160 samples (20 ms)
samples=reshape(x,160,[])
% allocate output signal matrix
nsamples =  length(samples(:,:))
output=zeros(160,nsamples)
% for each segment of 20ms
for s= 1:length(samples(:,:))
	xs = samples(:,s)
	energy = bitshift(sumsq(xs),-15)
	noisethreshold = noisedetector(energy)
	isnoise = (energy<=noisethreshold)
	% for each filter banks
	for c=1:length(coeffs(:,:,:))
		b = coeffs(1,:,c)
		a = coeffs(2,:,c)
		y = filter(b, a, xs)
		energy = bitshift(sumsq(y),-16)
		% if noise, smooth the energy over 1s (50 segments)
		if (isnoise)
			% TODO
		end
		% compute gain (TODO with suppression curve)
		g=0.975
		% apply gain
		ya = y*[g]
		% sum/sub 
		if (mod(c,2))
			yo = yo + ya
		else
			yo = yo - ya
		end
	end
	% append
	output(:,c) = yo
end
% TODO: write out output to wav