exec(open("Modified_data/testdr.dr").read())
#exec(open("Modified_data/realtime.py").read())


# Environment and parameters
dyn.rover.env.gravity = [0.0, 0.0, -1.62]
dyn.rover.env.mass    = 2000
dyn.rover.env.inertia = 200    
dyn.rover.env.cd      = 0.2          
dyn.rover.env.maxThrust       = 200   
dyn.rover.env.maxSteer        = 20    
dyn.rover.env.steerDamp       = 20   


# Motor and steering
dyn.rover.motor.sample_time_array    = [0, 12, 24, 36, 48, 60,  72,  84,  96, 108, 120]
dyn.rover.motor.thrust_sample_values = [1,  1,  1,  1,  1,  1,   1,   1,   1,   1,   1]
dyn.rover.motor.steer_sample_values  = [0,  0,  0,  0,  1,  1,   0,   -1,   -1,   0,   0]


# Position and velocity
dyn.rover.position[0] = 0.0
dyn.rover.position[1] = 0.0
dyn.rover.position[2] = 0.0
dyn.rover.velocity[0] = 0.0
dyn.rover.velocity[1] = 0.0
dyn.rover.velocity[2] = 0.0
#dyn.rover.phi         = 0.785398
dyn.rover.phi         =0.0
dyn.rover.omega       = 0.0

# Time
dyn.rover.mission_time      = 0.0
dyn.rover.mission_time_rate = 1.0






trick.exec_set_terminate_time(120.0)
