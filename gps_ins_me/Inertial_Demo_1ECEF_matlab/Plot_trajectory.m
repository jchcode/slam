function Plot_trajectory(profile)
% Plot_trajectory - Plots a motion trajectory

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



figure;

%% 1  North-Earth displacement
[R_N,R_E] = Radii_of_curvature(profile(1,2));
subplot(1, 2, 1);
plot(...
    ((profile(:,3) - profile(1,3)) * (R_E + profile(1,4)) * cos(profile(1,2))),...
    ((profile(:,2) - profile(1,2)) * (R_N + profile(1,4))),...
    'b','LineWidth',1.5...
    );
xlabel('Earth displacement, m');
ylabel('North displacement, m');
title('North-Earth displacement, m');

%% 2  Down displacement(m)
subplot(1, 2, 2);
plot(profile(:,1),(profile(1,4) - profile(:,4)),'g','LineWidth',1.5);
xlabel('Time, s');
ylabel('Down displacement, m');
title('Down displacement, m');

end



