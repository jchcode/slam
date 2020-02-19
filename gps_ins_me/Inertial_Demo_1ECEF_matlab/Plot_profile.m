function Plot_profile(profile)
% Plot_profile - Plots a motion profile

% Input:
% profile      Array of motion profile data to plot
% Format is
% Column 1: time (sec)
% Column 2: latitude (rad)
% Column 3: longitude (rad)
% Column 4: height (m)
% Column 5: north velocity (m/s)
% Column 6: east velocity (m/s)
% Column 7: down velocity (m/s)
% Column 8: roll angle of body w.r.t NED (rad)
% Column 9: pitch angle of body w.r.t NED (rad)
% Column 10: yaw angle of body w.r.t NED (rad)

fig = figure;
set(fig,'units','normalized');
set(fig,'OuterPosition',[0.05,0.4,0.45,0.6]);



%% 1   Position
% 1.1  North displacement(m)
[R_N,R_E] = Radii_of_curvature(profile(1,2));
subplot(3,3,1);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0.9,0.45,0]);
plot(profile(:,1),((profile(:,2) - profile(1,2)) * (R_N + profile(1,4))),...
    'LineWidth',1.5);
title('North displacement, m');
set(gca,'OuterPosition',[0.01,0.68,0.32,0.31]);

% 1.2  East displacement(m)
subplot(3,3,2);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0,0.9,0.45]);
plot(profile(:,1),((profile(:,3) - profile(1,3)) * (R_E + profile(1,4)) *...
    cos(profile(1,2))),'LineWidth',1.5);
title('East displacement, m');
set(gca,'OuterPosition',[0.34,0.68,0.32,0.31]);

% 1.3  Down displacement(m)
subplot(3,3,3);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0.45,0,0.9]);
plot(profile(:,1),(profile(1,4) - profile(:,4)),'LineWidth',1.5);
title('Down displacement, m');
set(gca,'OuterPosition',[0.67,0.68,0.32,0.31]);



%% 2   Velocity
% 2.1  North velocity(m/s)
subplot(3,3,4);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0.9,0,0.45]);
plot(profile(:,1),profile(:,5),'LineWidth',1.5);
title('North velocity, m/s');
set(gca,'OuterPosition',[0.01,0.36,0.32,0.31]);

% 2.2  East velocity(m/s)
subplot(3,3,5);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0.45,0.9,0]);
plot(profile(:,1),profile(:,6),'LineWidth',1.5);
title('East velocity, m/s');
set(gca,'OuterPosition',[0.34,0.36,0.32,0.31]);

% 2.3  Down velocity(m/s)
subplot(3,3,6);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0,0.45,0.9]);
plot(profile(:,1),profile(:,7),'LineWidth',1.5);
title('Down velocity, m/s');
set(gca,'OuterPosition',[0.67,0.36,0.32,0.31]);



%% 3   Attitude
% 3.1  Bank(deg)
subplot(3,3,7);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0,0.7,0.7]);
plot(profile(:,1),rad2deg(profile(:,8)),'LineWidth',1.5);
xlabel('Time, s');
title('Bank, deg');
set(gca,'OuterPosition',[0.01,0,0.32,0.35]);

% 3.2  Elevation(deg)
subplot(3,3,8);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0.7,0,0.7]);
plot(profile(:,1),rad2deg(profile(:,9)),'LineWidth',1.5);
xlabel('Time, s');
title('Elevation, deg');
set(gca,'OuterPosition',[0.34,0,0.32,0.35]);

% 3.3  Heading(deg)
subplot(3,3,9);
set(gca,'NextPlot','replacechildren');
set(gca,'ColorOrder',[0.7,0.7,0]);
plot(profile(:,1),rad2deg(profile(:,10)),'LineWidth',1.5);
xlabel('Time, s');
title('Heading, deg');
set(gca,'OuterPosition',[0.67,0,0.32,0.35]);

end
