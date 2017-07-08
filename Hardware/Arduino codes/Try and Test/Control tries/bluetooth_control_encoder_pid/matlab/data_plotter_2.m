% Step response ref 40.rpm + noise rejection 
% PID : 0.5 1.25 0.25 
% Filter : 0.25
% Sample_Time 100 ms

V = [
0.00		0.00
10.00		10.00
13.33		13.33
16.67		13.33
13.33		13.33
16.67		16.67
13.33		13.33
20.00		16.67
23.33		23.33
20.00		20.00
23.33		23.33
30.00		26.67
26.67		26.67
30.00		26.67
30.00		30.00
33.33		33.33
33.33		33.33
36.67		33.33
33.33		33.33
36.67		36.67
40.00		36.67
36.67		36.67
36.67		36.67
40.00		40.00
40.00		40.00
36.67		36.67
43.33		40.00
40.00		43.33
40.00		36.67
40.00		40.00
43.33		43.33
40.00		40.00
40.00		36.67
40.00		43.33
43.33		40.00
40.00		43.33
40.00		40.00
40.00		40.00
40.00		40.00
40.00		40.00
40.00		43.33
40.00		40.00
40.00		36.67
43.33		43.33
40.00		40.00
40.00		40.00
40.00		40.00
40.00		40.00
43.33		43.33
40.00		40.00
40.00		36.67
40.00		40.00
40.00		40.00
40.00		40.00
40.00		40.00
40.00		40.00
40.00		36.67
43.33		40.00
36.67		43.33
40.00		36.67
43.33		40.00
40.00		40.00
36.67		40.00
40.00		40.00
40.00		40.00
40.00		40.00
36.67		40.00
40.00		40.00
36.67		40.00
40.00		40.00
40.00		40.00
40.00		40.00
36.67		36.67
40.00		43.33
43.33		40.00
36.67		40.00
36.67		40.00
33.33		40.00
26.67		40.00
30.00		40.00
26.67		40.00
30.00		43.33
23.33		36.67
26.67		40.00
26.67		43.33
26.67		36.67
26.67		40.00
30.00		40.00
26.67		40.00
30.00		40.00
30.00		36.67
30.00		40.00
33.33		43.33
30.00		36.67
33.33		40.00
33.33		40.00
33.33		40.00
33.33		40.00
36.67		40.00
33.33		40.00
36.67		36.67
36.67		43.33
36.67		36.67
36.67		43.33
36.67		36.67
36.67		40.00
40.00		40.00
40.00		40.00
36.67		40.00
40.00		40.00
40.00		43.33
40.00		36.67
36.67		40.00
40.00		40.00
40.00		40.00
40.00		40.00
36.67		40.00
40.00		36.67
40.00		40.00
40.00		43.33
40.00		36.67
40.00		40.00
40.00		40.00
46.67		40.00
56.67		40.00
56.67		40.00
56.67		40.00
53.33		40.00
56.67		40.00
56.67		43.33
56.67		36.67
53.33		40.00
56.67		43.33
53.33		40.00
53.33		40.00
53.33		40.00
53.33		43.33
50.00		40.00
50.00		40.00
50.00		40.00
46.67		43.33
46.67		40.00
43.33		40.00
46.67		40.00
43.33		40.00
43.33		40.00
40.00		40.00
43.33		40.00
43.33		43.33
43.33		36.67
40.00		40.00
40.00		40.00
43.33		40.00
40.00		40.00
40.00		36.67
36.67		40.00
40.00		43.33
40.00		36.67
40.00		40.00
40.00		40.00
36.67		40.00
40.00		40.00
40.00		36.67
40.00		40.00
];

V_left_new = V(:,1);
V_right_new = V(:,1);

for n=3:1:length(V)-2
    V_left_new(n) = (V(n-2,1) + V(n-1,1) + V(n,1) + V(n+1,1) + V(n+2,1))/5;
    V_right_new(n) = (V(n-2,2) + V(n-1,2) + V(n,2) + V(n+1,2) + V(n+2,2))/5;
end
%V_left = V(:,1);
%V_right = V(:,2);

figure;
plot(V_left_new);
hold on;
plot(V_right_new);
hold off;