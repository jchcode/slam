% Inertial Demo_ECI
% Script --- Inertial navigation demostration
% Profile_1 (60s artificial car motion with two 90 deg turns)
% ECI-frame inertial navigation equations
% Tactical-grade IMU error model



clc, clear, clf, close all
%% Constants
deg_to_rad = pi / 180;
rad_to_deg = 180 / pi;
micro_g_to_meters_per_second_squared = 9.80665e-6;   % micro-g convert to m/s^2



%% 1   Configuration
% 1.1  Input and output filename
% input truth motion profile filename
input_profile_name = 'Profile_1.csv';
% output motion profile filename
output_profile_name = 'Inertial_Demo_1ECI_Profile.csv';
% output errors filename
output_errors_name = 'Inertial_Demo_1ECI_Errors.csv';

% 1.2 Initialization errors
% position initialization error(m, NED)
initialization_errors.delta_r_eb_n = [4; 2; 3];
% velocity initialization error(m/s, NED)
initialization_errors.delta_v_eb_n = [0.05; -0.05; 0.1];
% attitude initialization error(deg convert to rad, NED)
initialization_errors.delta_eul_nb_n = [-0.05; 0.04; 1] * deg_to_rad;

% 1.3  IMU model parameters
% accelerometer bias(micro-g convert to m/s^2, body axes)
IMU_errors.b_a = [900; -1300; 800]...
 * micro_g_to_meters_per_second_squared;
% gyro bias(deg/h convert to rad/s, body axes)
IMU_errors.b_g = [-9; 13; -8] * deg_to_rad / 3600;
% Accelerometer scale factor errors and cross-coupling errors
% (parts per million convert to unitless)
IMU_errors.M_a = [500, -300, 200; -150, -600, 250; -250, 100, 450]...
 * 1e-6;
% Gyro scale factor errors and cross-coupling  errors
% (parts per million convert to unitless)
IMU_errors.M_g = [400, -300, 250; 0, -300, -150; 0, 0, -350] * 1e-6;
% Gyro g-dependent bias(deg/h/g convert to rad*s/m)
IMU_errors.G_g = [0.9, -1.1, -0.6; -0.5, 1.9, -1.6; 0.3,  1.1, -1.3]...
 * deg_to_rad / (3600 * 9.80665);
% Accelerometer noise root PSD
% (100 micro-g per root Hz, convert to m*s^-1.5)
IMU_errors.accel_noise_root_PSD = 100 *...
    micro_g_to_meters_per_second_squared;
% Gyro noise root PSD
% (0.01 deg per root hour, convert to rad*s^-0.5)
IMU_errors.gyro_noise_root_PSD = 0.01 * deg_to_rad / 60;
% Accelerometer quantization level(m/s^2)
IMU_errors.accel_quant_level = 1e-2;
% Gyro quantization level(rad/s)
IMU_errors.gyro_quant_level = 2e-4;

% % 1.4  Seeding of random number generator
% % Seeding of the random number generator for reproducability
% % Change this value for a different random number sequence
% s = RandStream('mt19937ar', 'Seed', 1);
% RandStream.setGlobalStream(s);



%% 2   Inertial navigation solution in ECI frame
% 2.1  Read in the truth motion profile from .csv format filename
[in_profile, no_epochs, ok] = Read_profile(input_profile_name);
if ~ok
	return;
end   % end if ~ok

% 2.2  ECI inertial navigation simulation
[out_profile, out_errors] = Inertial_navigation_ECI(...
in_profile, no_epochs, initialization_errors, IMU_errors);

% 2.3  Plot the input motion profile and the errors
Plot_profile(in_profile);
Plot_errors(out_errors);
Plot_trajectory(out_profile);

% 2.4  Write output profile and errors file
Write_profile(output_profile_name, out_profile);
Write_errors(output_errors_name, out_errors);


























