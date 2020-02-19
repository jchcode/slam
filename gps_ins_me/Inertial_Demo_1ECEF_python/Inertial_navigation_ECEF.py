def Inertial_navigation_ECEF(in_profile, no_epochs,\
initialization_errors, IMU_errors):
    # Inertial_navigation_ECEF - Simulates inertial navigation using ECEF
    # navigation equations and kinematic model

    # Inputs:
    # in_profile   True motion profile array
    # no_epochs    Number of epochs of profile data
    # initialization_errors
    #   .delta_r_eb_n     position error resolved along NED (m)
    #   .delta_v_eb_n     velocity error resolved along NED (m/s)
    #   .delta_eul_nb_n   attitude error as NED Euler angles (rad)
    # IMU_errors
    #   .b_a              Accelerometer biases (m/s^2)
    #   .b_g              Gyro biases (rad/s)
    #   .M_a              Accelerometer scale factor and cross coupling errors
    #   .M_g              Gyro scale factor and cross coupling errors            
    #   .G_g              Gyro g-dependent biases (rad-sec/m)             
    #   .accel_noise_root_PSD   Accelerometer noise root PSD (m s^-1.5)
    #   .gyro_noise_root_PSD    Gyro noise root PSD (rad s^-0.5)
    #   .accel_quant_level      Accelerometer quantization level (m/s^2)
    #   .gyro_quant_level       Gyro quantization level (rad/s)

    # Outputs:
    #   out_profile   Navigation solution as a motion profile array
    #   out_errors    Navigation solution error array

    #  Format of motion profiles:
    #  Column 1: time (sec)
    #  Column 2: latitude (rad)
    #  Column 3: longitude (rad)
    #  Column 4: height (m)
    #  Column 5: north velocity (m/s)
    #  Column 6: east velocity (m/s)
    #  Column 7: down velocity (m/s)
    #  Column 8: roll angle of body w.r.t NED (rad)
    #  Column 9: pitch angle of body w.r.t NED (rad)
    #  Column 10: yaw angle of body w.r.t NED (rad)

    # Format of errors array:
    #  Column 1: time (sec)
    #  Column 2: north position error (m)
    #  Column 3: east position error (m)
    #  Column 4: down position error (m)
    #  Column 5: north velocity (m/s)
    #  Column 6: east velocity (m/s)
    #  Column 7: down velocity (m/s)
    #  Column 8: attitude error about north (rad)
    #  Column 9: attitude error about east (rad)
    #  Column 10: attitude error about down = heading error  (rad)



    # Initialize true navigation solution
    old_time = in_profile[0, 0]
    true_L_b = in_profile[0, 1]
    true_lambda_b = in_profile[0, 2]
    true_h_b = in_profile[0, 3]
    true_v_eb_n = in_profile[0:1, 4:7].T
    true_eul_nb = in_profile[0:1, 7:10].T
    true_C_b_n = Euler_to_CTM(true_eul_nb).T
