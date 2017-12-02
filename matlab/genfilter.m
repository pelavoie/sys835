clear
fc=[60 150 250 350 450 570 700 840 1000 1170 1370 1600 1850 2150 2500 2900 3400];
bw=[80 100 100 100 110 120 140 150 160 190 210 240 280 320 380 450 550];
fs=8000;
fn=fs/2;
% generate coefficients for filter bank
for c= 1:length(fc)
	b2 = bw(c)/2;
	fmin = fc(c)-b2;
	fmax = fc(c)+b2;
	[b, a] = butter(2, [fmin fmax]/fn);
	coeffs(:,:,c) = [b ; a];
end
printf("float b\[%d\]\[4\] \= \{\n", length(coeffs(:,:,:)));
for c=1:length(coeffs(:,:,:))
	printf("\{ %f, %f, %f, %f\},\n",-coeffs(2,5,c),-coeffs(2,4,c),-coeffs(2,3,c),-coeffs(2,2,c));
end
printf("\};\n");
printf("float gains\[%d\] \= \{\n", length(coeffs(:,:,:)));
for c=1:length(coeffs(:,:,:))
	printf(" %.9e,\n", 1/coeffs(1,1,c));
end
printf("\};\n");