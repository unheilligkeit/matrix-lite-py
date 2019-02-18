#ifndef SENSORS_SENSOR_H
#define SENSORS_SENSOR_H

// IMU //
struct imu_struct {
    // Accelerometer Output
    float accel_x;
    float accel_y;
    float accel_z;
    // Gyroscope Output
    float gyro_x;
    float gyro_y;
    float gyro_z;
    // Yaw, Pitch, Roll Output
    float yaw;
    float pitch;
    float roll;
    // Magnetometer Output
    float mag_x;
    float mag_y;
    float mag_z;
};

class imu {
    public:
    imu();
    ~imu();

    imu_struct read();
};

// UV //
struct uv_struct {
    float uv;
};

class uv {
    public:
    uv();
    ~uv();

    uv_struct read();
};

#endif