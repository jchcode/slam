% Inertial_Demo_1ECEF
% Script --- Inertial navigation demostration
% Profile_1 (60s artificial car motion with two 90 deg turns)
% ECEF-frame inertial navigation equations
% Tactical-grade IMU error model



clc, clear, clf, close all
%% Constants
deg_to_rad = pi / 180;
rad_to_deg = 1/deg_to_rad;
micro_g_to_meters_per_second_squared = 9.80665E-6;



%% 1   Configuration
% 1.1  Input and output filename
% Input truth motion profile filename
input_profile_name = 'Profile_1.csv';
% Output motion profile and error filenames
output_profile_name = 'Inertial_Demo_1ECEF_Profile.csv';
output_errors_name = 'Inertial_Demo_1ECEF_Errors.csv';

% 1.2 Initialization errors
% Position initialization error (m; @N,E,D)
initialization_errors.delta_r_eb_n = [4;2;3];
% Velocity initialization error (m/s; @N,E,D)
initialization_errors.delta_v_eb_n = [0.05;-0.05;0.1];
% Attitude initialization error (deg, converted to rad; @N,E,D)
initialization_errors.delta_eul_nb_n = [-0.05;0.04;1]*deg_to_rad; % rad

% 1.3  IMU model parameters
% Accelerometer biases (micro_g, converted to m/s^2; body axes)
IMU_errors.b_a = [900;-1300;800] * micro_g_to_meters_per_second_squared;
% Gyro biases (deg/hour, converted to rad/sec; body axes)
IMU_errors.b_g = [-9;13;-8] * deg_to_rad / 3600;
% Accelerometer scale factor and cross coupling errors (ppm, converted to
% unitless; body axes)
IMU_errors.M_a = [500, -300, 200;...
                 -150, -600, 250;...
                 -250,  100, 450] * 1E-6;
% Gyro scale factor and cross coupling errors (ppm, converted to unitless;
% body axes)
IMU_errors.M_g = [400, -300,  250;...
                    0, -300, -150;...
                    0,    0, -350] * 1E-6;             
% Gyro g-dependent biases (deg/hour/g, converted to rad-sec/m; body axes)
IMU_errors.G_g = [0.9, -1.1, -0.6;...
                 -0.5,  1.9, -1.6;...
                  0.3,  1.1, -1.3] * deg_to_rad / (3600 * 9.80665);             
% Accelerometer noise root PSD (micro-g per root Hz, converted to m s^-1.5)                
IMU_errors.accel_noise_root_PSD = 100 *...
    micro_g_to_meters_per_second_squared;
% Gyro noise root PSD (deg per root hour, converted to rad s^-0.5)                
IMU_errors.gyro_noise_root_PSD = 0.01 * deg_to_rad / 60;
% Accelerometer quantization level (m/s^2)
IMU_errors.accel_quant_level = 1E-2;
% Gyro quantization level (rad/s)
IMU_errors.gyro_quant_level = 2E-4;

% % 1.4  Seeding of random number generator
% % Seeding of the random number generator for reproducability
% % Change this value for a different random number sequence
% s = RandStream('mt19937ar', 'Seed', 1);
% RandStream.setGlobalStream(s);



%% 2   Inertial navigation solution in ECEF frame
% 2.1  Read in the truth motion profile from .csv format filename
% Input truth motion profile from .csv format file
[in_profile,no_epochs,ok] = Read_profile(input_profile_name);

% End script if there is a problem with the file
if ~ok
    return;
end %if

% 2.2  ECEF Inertial navigation simulation
[out_profile,out_errors] = Inertial_navigation_ECEF(in_profile,no_epochs,...
    initialization_errors,IMU_errors);

% 2.3  Plot the input motion profile and the errors
close all;
Plot_profile(in_profile);
Plot_errors(out_errors);
Plot_trajectory(out_profile);

% 2.4  Write output profile and errors file
Write_profile(output_profile_name,out_profile);
Write_errors(output_errors_name,out_errors);

% Ends