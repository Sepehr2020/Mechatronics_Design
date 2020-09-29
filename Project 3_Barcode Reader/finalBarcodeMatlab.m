clc
clear
close all

A=csvread('C 6.csv');% Open the data we collect from the paper 
PixelColor= A(1:end,4);% Build a matrix 
% { # Row = number of datas we collected, # col = 4 }


% Apply moving average to filter out higher frequency noise

WndwSz=500;% window size of our moving average

L_avg=0*PixelColor(1:end-(WndwSz-1)); % initializing the array for moving average datas 
% We could just type L_avg = 0;

% Fill up the array as we move the window 
for i=1:length(PixelColor)-(WndwSz-1)% Start from first data till All-(window size - 1) because we would run out of datas otherwise
    
    L_avg(i)=sum(PixelColor(i:i+(WndwSz-1)))/WndwSz;% Get the avg value of each window: sum the datas in each window and devide it by their quantity
end

% Plot Raw data vs Filtered
subplot(2,1,1)% Plot on top half
plot(L_avg,'r')% Plot L_avg array in red color


% Example solution (y2-y1)/(x2-x1)
L_Der=L_avg(2:end)-L_avg(1:end-1);% Final value of array - First value of array (yn-y1)
L_Der = times (10,(L_Der));% Increasing the amplitude of our deriv. graph, so it decreases chances of false peaks
% Because as the difference in real and false peaks increases, later on at
% MinPeakDistance we can choose the real one easier


% Apply moving derivative to find the change in colors

WndwSz=500;% window size of our moving derivative 

L_Der_Avg=0*L_Der(1:end-(WndwSz-1));% initializing the array for moving derivatives datas 
% We could just type L_Der = 0;

% Fill up the array as we move the window 
for i=1:length(L_Der)-(WndwSz-1)% Same logic as previous moving window
    % Start from the first data till the All-(window size -1)
    
    L_Der_Avg(i)=abs(sum(L_Der(i:i+(WndwSz-1)))/WndwSz);%Get the avg value of that window and set it to one element of the array
end



% Setting limits for picking the "heights" and "distance apparts" between two peaks in the L_Der_Avg graphs 
[PKS,LOCS]=findpeaks(L_Der_Avg,'MinPeakHeight',.07,'MinPeakDistance',300);

subplot(2,1,2)% Plot on bottom half
plot(L_Der_Avg)% Plot L_Der_Avg array 
hold on % Wait to apply the limits and plot both graphs together
plot(LOCS,PKS,'om')% Select the set limits (Distance appart, Heights, Picks those points that satisfies the limits)

% Find Widths
Widths=(LOCS(2:end)-LOCS(1:end-1))% Final Location - First Location (xn - x1)

% Scale to 1:3 ratio
Widths = floor(Widths/min(Widths))% Devide all Widths to smallest Width and round it to lower integer


% Find the character in the Look Up Table
Code39Pattern=sprintf('%d%d%d%d%d%d%d%d%d',Widths); % Print the 1:3 ratio in right table as an output 
LUT= load('LUT.mat');% Open the LookUpTable 
MyCellArray=LUT.ans(:,2); % Build a matrix of 26 rows and 2 coloumns 
index = find(strcmp(MyCellArray,Code39Pattern)) % Compare the collected 1:3 ratio with the LookUPTable ratios,
% When we find a similar 1:3 ratio, save the 1:3 series of numbers in index


% Give the letter output
ResultStr=sprintf('Pattern read as ASCII Char: > %c',LUT.ans{index,1})% Print the letter in front of "index" combinations of 1 and 3 in LUT
