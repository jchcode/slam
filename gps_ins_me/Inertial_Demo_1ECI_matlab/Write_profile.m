function Write_profile(filename,out_profile)
% Write_profile - outputs a motion profile in the following .csv format
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

% Inputs:
% filename     Name of file to write
% out_profile  Array of data to write


% Parameters
deg_to_rad = pi / 180;
rad_to_deg = 180 / pi;

% Convert output profile from radians to degrees
out_profile(:,2:3) = rad_to_deg * out_profile(:,2:3);
out_profile(:,8:10) = rad_to_deg * out_profile(:,8:10);

% Write output profile
dlmwrite(filename,out_profile,'newline','pc','precision',12);
% write matrix to ASCII-delimited file

end