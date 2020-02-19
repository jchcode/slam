function C = Euler_to_CTM(eul)
% Converts Euler angles to the corresponding coordinate transformation matrix

% Inputs: eul
% Euler angles describing rotation from local navigation frame to body
% frame in the order roll(rad), pitch(rad), yaw(rad)

% Outputs: C
% A coordinate transformation matrix from local navigation frame to body
% frame

sin_phi = sin(eul(1));
cos_phi = cos(eul(1));
sin_theta = sin(eul(2));
cos_theta = cos(eul(2));
sin_psi = sin(eul(3));
cos_psi = cos(eul(3));

C(1,1) = cos_theta * cos_psi;
C(1,2) = cos_theta * sin_psi;
C(1,3) = -sin_theta;
C(2,1) = -cos_phi * sin_psi + sin_phi * sin_theta * cos_psi;
C(2,2) = cos_phi * cos_psi + sin_phi * sin_theta * sin_psi;
C(2,3) = sin_phi * cos_theta;
C(3,1) = sin_phi * sin_psi + cos_phi * sin_theta * cos_psi;
C(3,2) = -sin_phi * cos_psi + cos_phi * sin_theta * sin_psi;
C(3,3) = cos_phi * cos_theta;

end