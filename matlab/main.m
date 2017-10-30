% Main
% 20 ms frame (160 samples @ 8kHz)
[x,fs]=audioread("car.wav")
c=1
ranges = zeros(128,1);
cumulative = zeros(128,1);

while(c<length(x))
	xs = x(c,c+159)
%	[threshold, ranges, cumulative] = noisedetector(xs, ranges, cumulative)
	for i=1:160
		
	c =c+160
end

% filter bank 
fc=[240 360 480 600 720 840 975 1125 1275 1425 1575 1750 1950 2150 2350 2600 2900 3200 3535]
bw=[120 120 120 120 120 120 150 150 150 150 150 200 200 200 300 300 300 300 370]
ts=125e-6
fs=8000
fn=fs/2
for c= 1:length(fc)
   b2 = bw(c)/2
   fmin = fc(c)-b2
   fmax = fc(c)+b2
   [b, a] = butter(2, [fmin fmax]/fn)
   y(c) = filter(b, a, x);
   
%   fvtool(b,a)
end

N=20e-3/ts
Vn2 = 

