% Step response ref 50.rpm 
% PID : 0.5 1.5 0.3 
% Filter : 0.2
% Sample_Time 200 ms
V = [

];

V_left_new = V(:,1);
V_right_new = V(:,1);

for n=3:1:length(V)-2
    V_left_new(n) = (V(n-2,1) + V(n-1,1) + V(n,1) + V(n+1,1) + V(n+2,1))/5;
    V_right_new(n) = (V(n-2,2) + V(n-1,2) + V(n,2) + V(n+1,2) + V(n+2,2))/5;
end
V_left = V(:,1);
V_right = V(:,2);

figure;
plot(V_left);
%plot(V_left_new);
hold on;
plot(V_right);
%plot(V_right_new);
hold off;