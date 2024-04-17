#include "../include/Environment.hh"

int Environment::default_data () {
    gravity[0] = 0.0;
    gravity[1] = 0.0;
    gravity[2] =-1.62;
    mass = 2000;       /* kg */
    inertia = 200;     /* kg*m^2 */
    cd = 500;          /* 1 */
    maxThrust = 200;   /* N */
    maxSteer  = 50;    /* N*m */
    steerDamp = 500;   /* N*s/m */

    return 0;
}
