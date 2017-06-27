



% % Import example maps for planning a path
% % Import Image
% filepath =('C:\Users\Yasmeen\Desktop\draw.bmp');
% image = imread(filepath);
% 
% % Convert to grayscale and then black and white image based on arbitrary
% % threshold.
% grayimage = rgb2gray(image);
% bwimage = grayimage < 0.5;
% 
% % Use black and white image as matrix input for binary occupancy grid
% map = robotics.BinaryOccupancyGrid(bwimage);
% 
% show(map)
% % figure

%%
map = robotics.BinaryOccupancyGrid(10,10,10);

xy = [1 1; 4.3 4.4; 2.6 2.3];
setOccupancy(map,xy,1);

show(map);

%set(gca,'XTick',0:0.4:10,'YTick',0:0.4:10)

%xlim([0 10])
%ylim([0 10])

%%
robotRadius = 0.4;
mapInflated = copy(map);
inflate(mapInflated, robotRadius);
show(mapInflated)


%%
prm = robotics.PRM;
prm.Map = mapInflated;
prm.NumNodes = 50;
prm.ConnectionDistance = 5;

%%
startLocation = [3 3];
endLocation = [5 5];
path = findpath(prm, startLocation, endLocation);


while isempty(path)
    % No feasible path found yet, increase the number of nodes
    prm.NumNodes = prm.NumNodes + 10;

    % Use the |update| function to re-create the PRM roadmap with the changed
    % attribute
    update(prm);

    % Search for a feasible path with the updated PRM
    path = findpath(prm, startLocation, endLocation);
end
% Display path
path;
show(prm)
grid on



% %%
% controller = robotics.PurePursuit;
% release(controller);
% controller.Waypoints = path;
% controller.DesiredLinearVelocity = 0.3;
% controller.MaxAngularVelocity = 2;
% controller.LookaheadDistance = 0.5;
% 
% robotCurrentLocation = path(1,:);
% robotGoal = path(end,:);
% 
% initialOrientation = 0;
% robotCurrentPose = [robotCurrentLocation initialOrientation];
% robot.setRobotPose(robotCurrentPose);
% distanceToGoal = norm(robotCurrentLocation - robotGoal);
% goalRadius = 0.1;
% 
% controlRate = robotics.Rate(10);
% while( distanceToGoal > goalRadius )
% 
%     % Compute the controller outputs, i.e., the inputs to the robot
%     [v, omega] = controller(robot.getRobotPose);
% 
%     % Simulate the robot using the controller outputs
%     drive(robot, v, omega);
% 
%     % Extract current location information from the current pose
%     robotCurrentPose = robot.getRobotPose;
% 
%     % Re-compute the distance to the goal
%     distanceToGoal = norm(robotCurrentPose(1:2) - robotGoal);
% 
%     waitfor(controlRate);
% end
% 



