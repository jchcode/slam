function eul = CTM_to_Euler(C)
% Converts coordinate transformation matrix to the corresponding Euler angles

% Inputs: C
% A coordinate transformation matrix from local navigation frame to body
% frame

% Outputs: eul
% Euler angles describing rotation from local navigation frame to body
% frame in the order roll(rad), pitch(rad), yaw(rad)

eul(1,1) = atan2(C(2,3),C(3,3));
eul(2,1) = - asin(C(1,3));    
eul(3,1) = atan2(C(1,2),C(1,1)); 

end