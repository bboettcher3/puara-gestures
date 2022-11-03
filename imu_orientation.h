/**************************************************************************
 *                                                                         *
 * Sensor Fusion code for estimating orientation of an IMU                 *
 * 2022 Joseph Malloch, Brady Boettcher                                    *
 * Input Devices and Music Interaction Laboratory                          *
 ***************************************************************************
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify    *
 * it under the terms of the GNU License.                                  *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU License V2 for more details.                                        *
 *                                                                         *
 ***************************************************************************/

#ifndef IMU_ORIENTATION_H
#define IMU_ORIENTATION_H

namespace ImuOrientation {
    // Data structures
    class Quaternion
    {
    public:
        Quaternion(): w(1), x(0), y(0), z(0) {}
        Quaternion(double w, double x, double y, double z): w(w), x(x), y(y), z(z) {}
        Quaternion(const Quaternion&) = default;
        Quaternion& operator= (const Quaternion&) = default;

        ~Quaternion() {}
        
        Quaternion multiply(Quaternion &q);
        Quaternion inverse();
        Quaternion conjugate();
        double dotProduct(Quaternion &q);
        Quaternion slerp(Quaternion &q, double weight);
        void normalize();
        Quaternion normalized();
        Quaternion getMinimumDistance(Quaternion &q);

        // Quaternion members
        double  w;
        double  x;
        double  y;
        double  z;
    private:
    };

    /* Only x, y, z set for inputs; roll, tilt and magnitude calculated by this class */
    typedef struct Axes
    {
        double  x;
        double  y;
        double  z;
        double  roll;
        double  tilt;
        double  magnitude;
    } Axes;

    /* Returns the current orientation as a quaternion */
    static Quaternion getOrientation(Quaternion &prev, Axes& accel, Axes& mag, Axes& gyro, double weight);

};

#endif
