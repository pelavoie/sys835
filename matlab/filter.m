% 20 ms frame
x = rand([1,160])
threshold = 1024
% noise detector
bin = zeros(128,1);
point = zeros(128,1);
energy=0
% frame energy
for s = 1:length(x)
    energy = energy + x(s)*x(s)
% 4ms decay
for i:1:128
	bin(i) = bin(i)*0.995
end
% update bin
i = energy/256
bin(i) = bin(i) + 160
% form area histogram
for j:1:128
	for i:1:j
		point(j) = point(j) + bin(i)
	end
end
% noise absent?
if (point(10) >= point(128)/4)
	candidate = 0
else
	% if noise present, find threshold candidate
	eightypct = 0.8*point(128)
	for j:10:128
		if (point(j)>=eightypct && point(j-1)<eightypct)
			candidate = j * 256 % energy quantum
			break
	end
end
if (candidate>=threshold)
	decay = 0.95
else
	decay = 0.60653
end
threshold = candidate + decay * (threshold - candidate)
threshold = max([1024 threshold])

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

