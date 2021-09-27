%% 
% Engineer: Sidong Guo
% Overview
% This algorithmn demodulates the incoming signal and calculates the tempo
% of the signal, then it calculates the timing-offset of the incoming
% simulated signal. 
% Design Name:   The octavis 
% File Name:     Syncing_algorithmn.m
%
% Inputs: 
%		tempo_s: controls the tempo of the song. This is a number between 0 and 1
%		fz: sampling rate in kHz.
%       tempo_resolution: this is a value between 0 and 1. 1 being full 
%           resolution. Be careful setting this too high. 1 will lock up
%           your computer.
%       time_offset: This is the delay to the start of the song. This is an
%           index to the time scale, so the actual delay amount is
%           determined by multiple factors
%       tempo_m: the tempo as measured by the algorithmn 
% Credit: Conductor_simulation.m and simulation_world.m credited to
% Prof.Timothy Brothers 
%
% History:       Sep 11 2021 File created
%
%-----------------------------------------------------
clc
clear
close all

%% Variable setup 
fz=5000; %sampling frequency%
tempo_resolution = .05;
time_offset = 60;

%%
tempo_s=0.8;
[song_freq_Hz, song_duration_s] = conductor_simulation(tempo_s,4);
% conductor plays each note at a tempo of 0.2, octave 4%
cumulative_duration_s = zeros(1, length(song_duration_s));
cumulative_duration_s(1) =  song_duration_s(1);
for i=2:length(song_duration_s)
	cumulative_duration_s(i) = song_duration_s(i) + cumulative_duration_s(i-1);
end

total_duration_s = max(cumulative_duration_s);
time_s = 0:(1/fz):total_duration_s;	%create a time vector
time_s(length(time_s)) = total_duration_s;

%% Create the digital signal
min_time_index = 1; %start the min time index at the start
% loop through all the freqs and generate a sin wave for each freq
for i=1:length(song_freq_Hz)
	max_time_index = find(time_s >= cumulative_duration_s(i),1); %find the times that correspond to this duration of time
	digital_note = sin(2*pi*song_freq_Hz(i)*time_s(min_time_index:max_time_index)); %create the actual note
	min_time_index = max_time_index + 1; %shift to the next time region.
	if(i == 1)
        digital = digital_note;
    else
        digital = [digital, digital_note];
    end
end

%% Create a signal to test the system
%%Put two copies of the song together
signal = [digital, digital];
signal = circshift(signal, time_offset);


%soundsc(signal)
%% Some weird envelop
D=20;
signal=signal(1:floor(length(signal)/2));
sign_sqr=2*signal.*signal;
%sign_down=downsample(sign_sqr,D);
sign_fir = lowpass(sign_sqr,30,fz);
sign_final=sqrt(sign_fir);
figure()
plot(1:length(sign_final),sign_final);

%digital signal only for testing purpose 
%digi_sqr=2*digital.*digital;
%digi_down=downsample(digi_sqr,D);
%digi_fir = lowpass(digi_sqr,30,fz);
%digi_final=sqrt(digi_fir);
%figure()
%plot(1:length(digi_final),digi_final);
%For an octave as low as 1, the minimum frequency is around 33Hz. 

%% Find the time difference of a resting period
count=100;
rest_s=0;rest_ss=0;
rest_e=0;rest_ee=0;
while (1)
    if real(sign_final(count))>0.7 && real(sign_final(count+1))<0.7
        rest_s=count;
    end
    if real(sign_final(count))<0.7 && real(sign_final(count+1))>0.7
        rest_e=count;
        break
    end
    count=count+1;
end
Interval=(rest_e-rest_s);
tempo_m=Interval/fz;
%% Find the measured time off-set
Expected_dur=2*(rest_e-rest_s);
off=abs(Expected_dur-rest_s);
Measured_timeoffset=off/5000;








