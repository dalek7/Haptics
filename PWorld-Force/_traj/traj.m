clc;clear;close all
A = load('traj_082412_220322.txt');


plot3(A(:,2), A(:,3), A(:,4),'.-');hold on;

g = 0.2;
h2 = quiver3(A(:,2), A(:,3), A(:,4), g*A(:,5), g*A(:,6), g*A(:,7), 0, ...
                    'AutoScale', 'off', 'MaxHeadSize', 2,'Color', 'r');
                

axis equal;
% axis([-2, 2, -2, 2, -2, 2]);

grid;
xlabel('X');
ylabel('Y');
zlabel('Z');
