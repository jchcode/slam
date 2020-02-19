function Omega = Skew_symmetric(omega)
% Calculates skew-symmetric matrix

% Inputs: omege
% omega       3-element vector

% Outputs: Omega
% Omega       3*3 matrix


Omega = [       0, -omega(3),  omega(2);...
         omega(3),         0, -omega(1);...
        -omega(2),  omega(1),         0];

end