% Main
% 20 ms frame (160 samples @ 8kHz)
c=1
ranges = zeros(128,1);
cumulative = zeros(128,1);
[x,fs]=audioread("car.wav")
noisethreshold=1024
% filter bank 
fc=[240 360 480 600 720 840 975 1125 1275 1425 1575 1750 1950 2150 2350 2600 2900 3200 3535]
bw=[120 120 120 120 120 120 150 150 150 150 150 200 200 200 300 300 300 300 370]
ts=125e-6
fn=fs/2
% process 20 ms samples
while(c<length(x))
	xs = x(c,c+159)
	energy=sumsq(xs)
	if (energy/256<128)
		[noisethreshold, ranges, cumulative] = noisedetector(energy, ranges, cumulative)
	end
	for c= 1:length(fc)
		b2 = bw(c)/2
		fmin = fc(c)-b2
		fmax = fc(c)+b2
		[b, a] = butter(2, [fmin fmax]/fn)
		y = filter(b, a, xs)
		% compute energy
		energy=sumsq(y)
		% if noise, smooth the enerygy
		% compute gain
		% apply gain
		% sum/sub and append
	end
	% append
	c = c+160
end

N=20e-3/ts
Vn2 = 

