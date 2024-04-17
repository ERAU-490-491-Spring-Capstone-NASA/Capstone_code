/*************************************************************************
PURPOSE: (Environment for Rover Sim)
LIBRARY DEPENDENCIES:
    ((rover/src/Environment.o))
**************************************************************************/
class Environment {
public:
    double gravity[3];  /* m/s^2 */
    double mass;        /* kg */
    double inertia;     /* kg*m^2 */
    double cd;          /* 1 */
    double maxThrust;   /* N */
    double maxSteer;    /* N*m */
    double steerDamp;   /* N*s/m */
    int default_data();
};
