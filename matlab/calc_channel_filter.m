function [b,a] = calc_channel_filter( fc, bw, freq_sample)
  % Calculate Butterworth Channel Filters.
  % Return parameters b,a of second order Butterworth filter
  % run 'pkg load signal' for octave
%pkg load signal 
fn=freq_sample/2;
fmin = fc - bw/2;
fmax = fc + bw/2;
[b, a] = butter(2, [fmin fmax]/fn);
end