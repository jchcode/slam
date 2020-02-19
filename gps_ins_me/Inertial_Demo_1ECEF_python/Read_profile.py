import numpy
from numpy import pi



def Read_profile(filename):
    # Read_profile - inputs a motion profile in the following .csv format

    # Column 1:  time (sec)
    # Column 2:  latitude (deg)
    # Column 3:  longitude (deg)
    # Column 4:  height (m)
    # Column 5:  north velocity (m/s)
    # Column 6:  east velocity (m/s)
    # Column 7:  down velocity (m/s)
    # Column 8:  roll angle of body w.r.t NED (deg)
    # Column 9:  pitch angle of body w.r.t NED (deg)
    # Column 10: yaw angle of body w.r.t NED (deg)

    # Inputs:
    # filename     Name of file to write

    # Outputs:
    # in_profile   Array of data from the file
    # no_epochs    Number of epochs of data in the file
    # ok           Indicates file has the expected number of columns


    # parameters
    deg_to_rad = pi / 180

    # read in the profile in .csv format
    in_profile = numpy.loadtxt(open(filename, "rb"), delimiter = ",", skiprows = 0)

    # determine size of the file
    no_epochs = in_profile.shape[0]
    no_columns = in_profile.shape[1]

    if no_columns != 10:
        print("Input file has the wrong number of columns")
        ok = False
    else:
        ok = True
        # convert degrees to radians
        in_profile[..., 1:3] = deg_to_rad * in_profile[..., 1:3]
        in_profile[..., 7:10] = deg_to_rad * in_profile[..., 7:10]

    return (in_profile, no_epochs, ok)

