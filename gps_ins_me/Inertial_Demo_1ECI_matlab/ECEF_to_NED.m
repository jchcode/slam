function [L_b,lambda_b,h_b,v_eb_n,C_b_n] = ECEF_to_NED(r_eb_e,v_eb_e,C_b_e)
% ECEF_to_NED - Converts Cartesian  to curvilinear position, velocity
% resolving axes from ECEF to NED and attitude from ECEF- to NED-referenced

% Inputs:
% r_eb_e        Cartesian position of body frame w.r.t. ECEF frame, resolved
%               along ECEF-frame axes (m)
% v_eb_e        velocity of body frame w.r.t. ECEF frame, resolved along
%               ECEF-frame axes (m/s)
% C_b_e         body-to-ECEF-frame coordinate transformation matrix

% Outputs:
% L_b           latitude (rad)
% lambda_b      longitude (rad)
% h_b           height (m)
% v_eb_n        velocity of body frame w.r.t. ECEF frame, resolved along
%               north, east, and down (m/s)
% C_b_n         body-to-NED coordinate transformation matrix



% Parameters
R_0 = 6378137; %WGS84 Equatorial radius in meters
e = 0.0818191908425; %WGS84 eccentricity



% Convert position using Borkowski closed-form exact solution
% From (2.113)
lambda_b = atan2(r_eb_e(2),r_eb_e(1));

% From (C.29) - (C.36)
k1 = sqrt(1 - e^2) * abs (r_eb_e(3));
k2 = e^2 * R_0;
beta = sqrt(r_eb_e(1)^2 + r_eb_e(2)^2);
E = (k1 - k2) / beta;
F = (k1 + k2) / beta;
P = 4/3 * (E*F + 1);
Q = 2 * (E^2 - F^2);
D = P^3 + Q^2;
V = (sqrt(D) - Q)^(1/3) - (sqrt(D) + Q)^(1/3);
G = 0.5 * (sqrt(E^2 + V) + E);
T = sqrt(G^2 + (F - V * G) / (2 * G - E)) - G;

% From (C.37)
L_b = sign(r_eb_e(3)) * atan((1 - T^2) / (2 * T * sqrt (1 - e^2)));

% From (C.38)
h_b = (beta - R_0 * T) * cos(L_b) +...
    (r_eb_e(3) - sign(r_eb_e(3)) * R_0 * sqrt(1 - e^2)) * sin (L_b);
   

   
% Calculate ECEF to NED coordinate transformation matrix using (2.150)
cos_lat = cos(L_b);
sin_lat = sin(L_b);
cos_long = cos(lambda_b);
sin_long = sin(lambda_b);
C_e_n = [-sin_lat * cos_long, -sin_lat * sin_long,  cos_lat;...
                   -sin_long,            cos_long,        0;...
         -cos_lat * cos_long, -cos_lat * sin_long, -sin_lat];   
% Transform velocity using (2.73)
v_eb_n = C_e_n * v_eb_e;




% Transform attitude using (2.15)
C_b_n = C_e_n * C_b_e;

end