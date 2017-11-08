function newthreshold = noisedetector(energy)
    persistent threshold;
    if (isempty(threshold))
        threshold = 1024;
    end
    persistent bin;
    if (isempty(bin))
        bin = zeros(128,1);
    end
    persistent point;
    if (isempty(point))
        point = zeros(128,1);
    end
    
	% noise detector
	% frame's energy
	% 4ms decay
	bin = bin*0.995;
	% update bin
	i = idivide(energy,256);
	if (i>128)
		i=128;
	end
	bin(i) = bin(i) + 160;
	% form area histogram
	for j=1:128
		point(j) = point(j) + sum(bin(1:j));
	end
	% noise absent?
	if (point(10) >= point(128)/4)
		candidate = 0;
	else
		% if noise present, find threshold candidate
		eightypct = 0.8*point(128);
		for j=10:128
			if (point(j)>=eightypct && point(j-1)<eightypct)
				candidate = j * 256; % energy quantum
				break
			end
		end
	end
	if (candidate>=threshold)
		decay = 0.95;
	else
		decay = 0.60653;
	end
	threshold = candidate + decay * (threshold - candidate);
	threshold = max([1024 threshold]);
    newthreshold = threshold ;
end