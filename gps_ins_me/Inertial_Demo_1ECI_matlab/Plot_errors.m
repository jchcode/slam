function Plot_errors(errors)
% Plot_errors - Plots navigation solution errors

% Input:
% errors      Array of error data to plot
% Format is
% Column 1: time (sec)
% Column 2: north position error (m)
% Column 3: east position error (m)
% Column 4: down position error (m)
% Column 5: north velocity error (m/s)
% Column 6: east velocity error (m/s)
% Column 7: down velocity error(m/s)
% Column 8: roll component of NED attitude error (rad)
% Column 9: pitch component of NED attitude error (rad)
% Column 10: yaw component of NED attitude error (rad)

fig = figure;
set(fig,'units','normalized');
set(fig,'OuterPosition',[0.5,0.4,0.45,0.6]);



%% 1   Position Error
% 1.1  north position error
subplot(3,3,1);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0.9,0.45,0]);
plot(errors(:,1),errors(:,2),'LineWidth',1.5);
title('North position error, m');
set(gca,'OuterPosition',[0.01,0.68,0.32,0.31]);

% 1.2  east position error
subplot(3,3,2);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0,0.9,0.45]);
plot(errors(:,1),errors(:,3),'LineWidth',1.5);
title('East position error, m');
set(gca,'OuterPosition',[0.34,0.68,0.32,0.31]);

% 1.3  down position error
subplot(3,3,3);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0.45,0,0.9]);
plot(errors(:,1),errors(:,4),'LineWidth',1.5);
title('Down position error, m');
set(gca,'OuterPosition',[0.67,0.68,0.32,0.31]);



%% 2   Velocity error
% 2.1  north velocity error
subplot(3,3,4);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0.9,0,0.45]);
plot(errors(:,1),errors(:,5),'LineWidth',1.5);
title('North velocity error, m/s');
set(gca,'OuterPosition',[0.01,0.36,0.32,0.31]);

% 2.2  east velocity error
subplot(3,3,5);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0.45,0.9,0]);
plot(errors(:,1),errors(:,6),'LineWidth',1.5);
title('East velocity error, m/s');
set(gca,'OuterPosition',[0.34,0.36,0.32,0.31]);

% 2.3  down velocity error
subplot(3,3,6);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0,0.45,0.9]);
plot(errors(:,1),errors(:,7),'LineWidth',1.5);
title('Down velocity error, m/s');
set(gca,'OuterPosition',[0.67,0.36,0.32,0.31]);



%% 3   Attitude error
% 3.1  attitude error about north
subplot(3,3,7);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0,0.7,0.7]);
plot(errors(:,1),rad2deg(errors(:,8)),'LineWidth',1.5);
xlabel('Time, s');
title('Attitude error about North, deg');
set(gca,'OuterPosition',[0.01,0,0.32,0.35]);

% 3.2  attitude error about east
subplot(3,3,8);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0.7,0,0.7]);
plot(errors(:,1),rad2deg(errors(:,9)),'LineWidth',1.5);
xlabel('Time, s');
title('Attitude error about East, deg');
set(gca,'OuterPosition',[0.34,0,0.32,0.35]);

% 3.3  heading error
subplot(3,3,9);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0.7,0.7,0]);
plot(errors(:,1),rad2deg(errors(:,10)),'LineWidth',1.5);
xlabel('Time, s');
title('Heading error, deg');
set(gca,'OuterPosition',[0.67,0,0.32,0.35]);

end