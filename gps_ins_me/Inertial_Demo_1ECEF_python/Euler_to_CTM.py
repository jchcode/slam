import numpy

def Euler_to_CTM(eul):
    # Converts Euler angles to the corresponding coordinate transformation matrix

    # Inputs: eul
    # Euler angles describing rotation from local navigation frame to body
    # frame in the order roll(rad), pitch(rad), yaw(rad)

    # Outputs: C
    # A coordinate transformation matrix from local navigation frame to body
    # frame



    sin_phi   = numpy.sin(eul[0, 0])
    cos_phi   = numpy.cos(eul[0, 0])
    sin_theta = numpy.sin(eul[1, 0])
    cos_theta = numpy.cos(eul[1, 0])
    sin_psi   = numpy.sin(eul[2, 0])
    cos_psi   = numpy.cos(eul[2, 0])

    C = numpy.zeros( (3, 3) )

    C[0, 0] = cos_theta * cos_psi
    C[0, 1] = cos_theta * sin_psi
    C[0, 2] = -sin_theta

    C[1, 0] = -cos_phi * sin_psi + sin_phi * sin_theta * cos_psi
    C[1, 1] = cos_phi * cos_psi + sin_phi * sin_theta * sin_psi
    C[1, 2] = sin_phi * cos_theta

    C[2, 0] = sin_phi * sin_psi + cos_phi * sin_theta * cos_psi
    C[2, 1] = -sin_phi * cos_psi + cos_phi * sin_theta * sin_psi
    C[2, 2] = cos_phi * cos_theta

    return C