#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#define EARTH_GRAVITY_MS2 9.80665
#define DEG_TO_RAD        0.017453292519943295769236907684886
#define RAD_TO_DEG        57.295779513082320876798154814105

MPU6050 mpu;

bool DMPReady = false;
uint8_t devStatus;
uint16_t packetSize;
uint8_t FIFOBuffer[64];

Quaternion q;
VectorInt16 aa;
VectorInt16 aaWorld;
VectorFloat gravity;
float ypr[3];
float retunValue[6];

void SetupGyro() {
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    Wire.begin();
    Wire.setClock(400000); // 400kHz I2C clock. Comment on this line if having compilation difficulties
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
    Fastwire::setup(400, true);
  #endif

  Serial.begin(115200);
  Serial.println(F("Initializing MPU6050..."));
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (true);
  }

  Serial.println("MPU6050 connected");
  devStatus = mpu.dmpInitialize();

  // Set offsets if needed
  mpu.setXGyroOffset(0);
  mpu.setYGyroOffset(0);
  mpu.setZGyroOffset(0);
  mpu.setXAccelOffset(0);
  mpu.setYAccelOffset(0);
  mpu.setZAccelOffset(0);

  if (devStatus == 0) {
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
    mpu.PrintActiveOffsets();
    mpu.setDMPEnabled(true);
    DMPReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
    Serial.println("DMP ready.");
  } else {
    Serial.print("DMP Initialization failed (code ");
    Serial.print(devStatus);
    Serial.println(")");
  }
}

float *getYawPitchRoll() {
  while (!mpu.dmpGetCurrentFIFOPacket(FIFOBuffer));
    mpu.dmpGetQuaternion(&q, FIFOBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    mpu.dmpGetAccel(&aa, FIFOBuffer);
    mpu.dmpConvertToWorldFrame(&aaWorld, &aa, &q);

    // Yaw, Pitch, Roll in degrees
    retunValue[0] = ypr[0] * RAD_TO_DEG;
    retunValue[1] = ypr[1] * RAD_TO_DEG;
    retunValue[2] = ypr[2] * RAD_TO_DEG;

    // Acceleration in world frame in m/s^2
    retunValue[3] = aaWorld.x * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2;
    retunValue[4] = aaWorld.y * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2;
    retunValue[5] = aaWorld.z * mpu.get_acce_resolution() * EARTH_GRAVITY_MS2;

    return retunValue;
    // // Output (for sending over UDP or serial)
    // Serial.print(yaw_deg); Serial.print(",");
    // Serial.print(pitch_deg); Serial.print(",");
    // Serial.print(roll_deg); Serial.print(",");
    // Serial.print(ax); Serial.print(",");
    // Serial.print(ay); Serial.print(",");
    // Serial.println(az);
}

/*#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

MPU6050 mpu;

bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void SetupGyro() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
    Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    // initialize device
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // Calibration Time: generate offsets and calibrate our MPU6050
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
}

// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

float *getYawPitchRoll() {
  while (!mpu.dmpGetCurrentFIFOPacket(fifoBuffer)); // Keep wait until get the Latest packet 
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
  ypr[0] = ypr[0] * 180/M_PI;
  ypr[1] = ypr[1] * 180/M_PI;
  ypr[2] = ypr[2] * 180/M_PI;
  return ypr;
}*/