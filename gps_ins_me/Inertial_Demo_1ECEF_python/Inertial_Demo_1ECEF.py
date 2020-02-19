'''
Inertial_Demo_1ECEF
Script --- Inertial navigation demostration
Profile_1 (60s artificial car motion with two 90 deg turns)
ECEF-frame inertial navigation equations
Tactical-grade IMU error model
'''



import sys
import numpy
from numpy import pi
from Read_profile import Read_profile



# Constants
deg_to_rad = pi / 180
rad_to_deg = 1 / deg_to_rad
micro_g_to_meters_per_second_squared = 9.80665e-6



# 1   Configuration
# 1.1 Input and  output filename
# input truth motion profile filename
input_profile_name = "Profile_1.csv"
# output motion profile and errors filenames
output_profile_name = "Inertial_Demo_1ECEF_Profile.csv"
output_errors_name = "Inertial_Demo_1ECEF_Errors.csv"

# 1.2 Initialization errors
class initialization_errors:
    # position initialization error (m; N,E,D)
    delta_r_eb_n = numpy.array([[4, 2, 3]]).T
    # velocity initialization error (m/s; N,E,D)
    delta_v_eb_n = numpy.array([[0.05, -0.05, 0.1]]).T
    # attitude initialization error (deg, converted to rad; N,E,D)
    delta_eul_nb_n = numpy.array([[-0.05, 0.04, 1]]).T * deg_to_rad

# 1.3 IMU model parameters
class IMU_errors:
    # accelerometer biases (micro_g, converted to m/s^2; body axes)
    b_a = numpy.array([[900, -1300, 800]]).T * \
    micro_g_to_meters_per_second_squared
    # gyro biases (deg/hour, converted to rad/sec; body axes)
    b_g = numpy.array([[-9, 13, -8]]).T * deg_to_rad / 3600
    # accelerometer scale factor and cross coupling errors
    # (parts per million, converted to unitless; body axes)
    M_a = numpy.array([[500, -300, 200], [-150, -600, 250], [-250, 100, 450]]) * 1e-6
    # gyro scale factor and cross coupling errors 
    # (parts per million, converted to unitless; body axes)
    M_g = numpy.array([[400, -300, 250], [0, -300, -150], [0, 0, -350]]) * 1e-6
    # gyro g-dependent biases (deg/hour/g, converted to rad-sec/m; body axes)
    G_g = numpy.array([[0.9, -1.1, -0.6], [-0.5, 1.9, -1.6], [0.3, 1.1, -1.3]]) * \
    deg_to_rad / (3600 * 9.80665)
    # accelerometer noise root PSD (micro_g per root Hz, converted to m s^-1.5)
    accel_noise_root_PSD = 100 * micro_g_to_meters_per_second_squared
    # gyro noise root PSD (deg per root hour, converted to rad per root second)
    gyro_noise_root_PSD = 0.01 * deg_to_rad / 60
    # accelerometer quantization level (m/s^2)
    accel_accel_quant_level = 1e-2
    # gyro quantization level (rad/s)
    gyro_quant_level = 2e-4



# 2   Inertial navigation solution in ECEF frame
# 2.1 Read in the truth motion profile from .csv format filename
# input truth motion profile from .csv format file
(in_profile, no_epochs, ok) = Read_profile(input_profile_name)
# end script if there is a problem with the file
if ok == False:
    sys.exit()

# 2.2 ECEF inertial navigation simulation
(out_profile, out_errors) = Inertial_navigation_ECEF(in_profile,\
no_epochs, initialization_errors, IMU_errors)


