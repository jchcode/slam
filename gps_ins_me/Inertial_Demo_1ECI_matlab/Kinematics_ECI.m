function [f_ib_b,omega_ib_b] = Kinematics_ECI(tor_i,C_b_i,...
        old_C_b_i,v_ib_i,old_v_ib_i,r_ib_i)
% Kinematics_ECI - calculates specific force and angular rate from input
% w.r.t and resolved along ECI-frame axes

% Inputs:
%   tor_i         time interval between epochs (s)
%   C_b_i         body-to-ECI-frame coordinate transformation matrix
%   old_C_b_i     previous body-to-ECI-frame coordinate transformation matrix
%   v_ib_i        velocity of body frame w.r.t. ECI frame, resolved along
%                 ECI-frame axes (m/s)
%   old_v_ib_i    previous velocity of body frame w.r.t. ECI frame, resolved
%                 along ECI-frame axes (m/s)
%   r_ib_i        Cartesian position of body frame w.r.t. ECI frame, resolved
%                 along ECI-frame axes (m)
% Outputs:
%   f_ib_b        specific force of body frame w.r.t. ECI frame, resolved
%                 along body-frame axes, averaged over time interval (m/s^2)
%   omega_ib_b    angular rate of body frame w.r.t. ECI frame, resolved
%                 about body-frame axes, averaged over time interval (rad/s)



if tor_i > 0

    % Obtain coordinate transformation matrix from the new attitude to the
    % old from (5.68)
    C_new_old = old_C_b_i' * C_b_i;

    % Calculate the approximate angular rate
    alpha_ib_b(1,1) = 0.5 * (C_new_old(3,2) - C_new_old(2,3));
    alpha_ib_b(2,1) = 0.5 * (C_new_old(1,3) - C_new_old(3,1));
    alpha_ib_b(3,1) = 0.5 * (C_new_old(2,1) - C_new_old(1,2));

    % Calculate and apply the scaling factor
    temp = acos(0.5 * (trace(C_new_old) - 1.0));
    if temp>2e-5 %scaling is 1 if temp is less than this
        alpha_ib_b = alpha_ib_b * temp/sin(temp);
    end %if temp
    
    % Calculate the angular rate
    omega_ib_b = alpha_ib_b / tor_i;
    
    % Calculate the specific force resolved about ECI-frame axes
    % From (5.18) and (5.20),
    f_ib_i = ((v_ib_i - old_v_ib_i) / tor_i) - Gravitation_ECI(r_ib_i);
    
    % Calculate the average body-to-ECI-frame coordinate transformation
    % matrix over the update interval using (5.84)
    mag_alpha = sqrt(alpha_ib_b' * alpha_ib_b);
    Alpha_ib_b = Skew_symmetric(alpha_ib_b);    
    if mag_alpha>1E-8
        ave_C_b_i = old_C_b_i * ((eye(3) + (1 - cos(mag_alpha)) /mag_alpha^2 ...
           * Alpha_ib_b + (1 - sin(mag_alpha) / mag_alpha) / mag_alpha^2 ...
           * Alpha_ib_b * Alpha_ib_b));
    else
        ave_C_b_i = old_C_b_i * (eye(3) + 0.5*Alpha_ib_b);
    end %if mag_alpha
    
    % Transform specific force to body-frame resolving axes using (5.81)
    f_ib_b = ave_C_b_i \ f_ib_i;
    
else
    % If time interval is zero, set angular rate and specific force to zero
    omega_ib_b = [0;0;0];
    f_ib_b = [0;0;0];
end %if tor_i

end
