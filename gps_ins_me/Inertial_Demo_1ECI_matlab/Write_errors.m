function Write_errors(filename,out_errors)
% Write_errors - outputs the errors in the following .csv format
% Column 1: time (sec)
% Column 2: north position error (m)
% Column 3: east position error (m)
% Column 4: down position error (m)
% Column 5: north velocity (m/s)
% Column 6: east velocity (m/s)
% Column 7: down velocity (m/s)
% Column 8: roll component of NED attitude error (rad)
% Column 9: pitch component of NED attitude error (rad)
% Column 10: yaw component of NED attitude error (rad)

% Inputs:
% filename     Name of file to write
% out_errors   Array of data to write


% Parameters
deg_to_rad = pi / 180;
rad_to_deg = 180 / pi;

% Convert attitude errors from radians to degrees
out_errors(:,8:10) = rad_to_deg * out_errors(:,8:10);

% Write output profile
dlmwrite(filename,out_errors,'newline','pc','precision',12);
% write matrix to ASCII-delimited file

end