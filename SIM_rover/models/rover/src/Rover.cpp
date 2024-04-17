/********************************* TRICK HEADER *******************************
PURPOSE: ( Simulate a lunar rover. )
LIBRARY DEPENDENCY:
    ((Rover.o))
*******************************************************************************/
#include "../include/Rover.hh"
#include <math.h>
#include <iostream>

int Rover::default_data() {

    env.default_data();
    motor.default_data();

    mission_time      = 0.0;
    mission_time_rate = 1.0;

    position[0] = 0.0;
    position[1] = 0.0;
    position[2] = 0.0;
    velocity[0] = 0.0;
    velocity[1] = 0.0;
    velocity[2] = 0.0;
    phi         = 0.0;
    omega       = 0.0;
    return (0);
}

int Rover::state_init() {
    motor.state_init();
    return (0);
}

int Rover::state_deriv() {

    mission_time_rate = 1.0;

    thrust_mag   = motor.thrust_magnitude( mission_time );
    steering_mag = motor.steer_magnitude( mission_time);


    double vel_magnitude = sqrt( velocity[0] * velocity[0] + velocity[1] * velocity[1] + velocity[2] * velocity[2]);
    
    drag_force[0] = env.cd*env.mass*velocity[0];
    drag_force[1] = env.cd*env.mass*velocity[1];
    drag_force[2] = env.cd*env.mass*velocity[2];

    thrust_force = thrust_mag*env.maxThrust;
    double vdot = thrust_force/env.mass;

    double acc_path[2];
    acc_path[0] = vdot;
    acc_path[1] = omega*vel_magnitude;


    acc[0]    = acc_path[0]*cos(phi) - acc_path[1]*sin(phi)- drag_force[0]/env.mass;
    acc[1]    = acc_path[0]*sin(phi) + acc_path[1]*cos(phi)- drag_force[1]/env.mass;
    acc[2]    = 0.0;
    omega_dot = (steering_mag*env.maxSteer -env.steerDamp*omega)/env.inertia;
    

   return(0);
}

#include "sim_services/Integrator/include/integrator_c_intf.h"

int Rover::state_integ() {

   int integration_step;

   load_state ( &mission_time, &position[0], &position[1], &position[2], &velocity[0], &velocity[1], &velocity[2], &phi, &omega, (double*)0);
   load_deriv ( &mission_time_rate, &velocity[0], &velocity[1], &velocity[2], &acc[0], &acc[1], &acc[2], &omega, &omega_dot, (double*)0);

   integration_step = integrate();
   unload_state ( &mission_time,
                  &position[0], &position[1], &position[2],
                  &velocity[0], &velocity[1], &velocity[2],
                  &phi, &omega,
                  (double*)0);

   return(integration_step);
}
