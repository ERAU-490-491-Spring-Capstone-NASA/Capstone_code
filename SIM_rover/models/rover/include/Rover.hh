/*************************************************************************
PURPOSE: (Simulate a lunar rover)
LIBRARY DEPENDENCIES:
    ((rover/src/Rover.o))
**************************************************************************/
#ifndef _rover_hh_
#define _rover_hh_

#include "Environment.hh"
#include "Motor.hh"

class Rover {
public:
    Environment env;
    Motor motor;

    double thrust_force;
    double drag_force[3];
    double total_force[3];
    double thrust_mag;
    double steering_mag;

    double mission_time ; /* s    time elapsed since launch */
    double mission_time_rate;
    double position[3] ;       /* m     xyz-position         */
    double velocity[3] ;       /* m/s   xyz-velocity         */
    double acc[3] ;            /* m/s2  xyz-acceleration     */
    double phi;                /* 1     azimuth              */
    double omega;              /* 1/s   angular rate         */
    double omega_dot;          /* 1/s^2 angular acceleration */

    int default_data();
    int state_init();
    int state_deriv();
    int state_integ();

};
#endif
