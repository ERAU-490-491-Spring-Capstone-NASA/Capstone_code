/********************************* TRICK HEADER *******************************
PURPOSE: ( Simulate a marsr. )
LIBRARY DEPENDENCY:
    ((Marsr.o))
*******************************************************************************/
#include "../include/Marsr.hh"
#include <math.h>
#include <iostream>

int Marsr::default_data() {

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
    mass_dry    = 2000;
    mass_fuel   = 8000;
    exhaust_vel = 2500;
    mass        = mass_dry + mass_fuel;
    return (0);
}

int Marsr::state_init() {
    motor.state_init();
    return (0);
}

int Marsr::state_deriv() {

    mission_time_rate = 1.0;

    thrust_mag   = motor.thrust_magnitude( mission_time );
    steering_mag = motor.steer_magnitude( mission_time);

    thrust_force = thrust_mag*env.maxThrust;

    if (mass_fuel > 0)
    {
        mass_rate = -thrust_force / exhaust_vel;
    } else
    {
        mass_rate = 0;
        thrust_force = 0;
    }

    mass = mass_dry + mass_fuel;


    acc[0]    = env.gravity[0] + thrust_force*cos(phi)/mass;
    acc[1]    = 0.0;
    acc[2]    = env.gravity[2] + thrust_force*sin(phi)/mass;

    omega_dot = -steering_mag*env.maxSteer /env.inertia;




    

   return(0);
}

#include "sim_services/Integrator/include/integrator_c_intf.h"

int Marsr::state_integ() {

   int integration_step;

   load_state ( &mission_time, &position[0], &position[1], &position[2], &velocity[0], &velocity[1], &velocity[2], &phi, &omega, &mass_fuel, (double*)0);
   load_deriv ( &mission_time_rate, &velocity[0], &velocity[1], &velocity[2], &acc[0], &acc[1], &acc[2], &omega, &omega_dot, &mass_rate, (double*)0);

   integration_step = integrate();
   unload_state ( &mission_time,
                  &position[0], &position[1], &position[2],
                  &velocity[0], &velocity[1], &velocity[2],
                  &phi, &omega, &mass_fuel,
                  (double*)0);

   return(integration_step);
}
