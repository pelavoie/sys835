function [threshold, bin, point] = noisedetector(energy, bin, point, threshold)
	% noise detector
	% frame's energy
	% 4ms decay
	for i=1:128
		bin(i) = bin(i)*0.995
	end
	% update bin
	i = energy/256
	bin(i) = bin(i) + 160
	% form area histogram
	for j=1:128
		for i=1:j
			point(j) = point(j) + bin(i)
		end
	end
	% noise absent?
	if (point(10) >= point(128)/4)
		candidate = 0
	else
		% if noise present, find threshold candidate
		eightypct = 0.8*point(128)
		for j=10:128
			if (point(j)>=eightypct && point(j-1)<eightypct)
				candidate = j * 256 % energy quantum
				break
			end
		end
	end
	if (candidate>=threshold)
		decay = 0.95
	else
		decay = 0.60653
	end
	threshold = candidate + decay * (threshold - candidate)
	threshold = max([1024 threshold])
endfunction