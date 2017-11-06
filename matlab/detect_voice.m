%function [threshold, bin, point] = detect_noise(energy, frame, point, threshold)
function voice_presence = detect_voice(frame_energy, voice_threshold)
  if (frame_energy > voice_threshold)
    voice_presence = true;
  else
    voice_presence = false;
  endif
endfunction