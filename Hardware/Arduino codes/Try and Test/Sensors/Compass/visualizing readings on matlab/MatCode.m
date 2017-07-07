clc;
figure;
axis([-1000 1000 -1000 1000]);
hold on;

S = serial('COM6','BaudRate',9600,'timeOut',.5);
fopen(S);
%if(S.BytesAvailable > 0)
%    Y = fread(S,S.BytesAvailable);
%end
if( S.BytesAvailable)
    X = fread(S,S.BytesAvailable);
end

while(1)
    X = fscanf(S,'%d');
    pause(0.1);
    if(X==0)
        break;
    end
end
v = 0;
U = 500;
X = zeros(1,U);
Y = zeros(1,U);
Z = zeros(1,U);

for i=1:1:U
    
    X(i) = fscanf(S,'%d');
    Y(i) = fscanf(S,'%d');
    Z(i) = fscanf(S,'%d');
    T = fscanf(S,'%d');
    plot(X(i),Y(i),'.');
    pause(0.01);
end

fclose(S);
disp('finished');

Xmax = max(X);
Xmin = min(X);
Ymax = max(Y);
Ymin = min(Y);
Xoffset = (Xmax + Xmin)/2;
Yoffset = (Ymax + Ymin)/2;

Xfactor = (Xmax - Xmin)/100;
Yfactor = (Ymax - Ymin)/100;

Xnew = (X-Xoffset)/Xfactor;
Ynew = (Y-Yoffset)/Yfactor;

plot(Xnew,Ynew,'.g');

