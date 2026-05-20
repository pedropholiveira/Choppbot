#include <MultiDriver.h>
#include <Choppbot.h>
#include <SyncDriver.h>
#include <StepMotor.h>

BasicStepperDriver stepperX(MOTOR_STEPS, DIR_X, STEP_X);
BasicStepperDriver stepperY(MOTOR_STEPS, DIR_Y, STEP_Y);
BasicStepperDriver stepperZ(MOTOR_STEPS, DIR_Z, STEP_Z);

SyncDriver controller(stepperX, stepperY, stepperZ);

float D_POLIA_1 = 9.55;                           // Stepper motor pulley diameter
float D_POLIA_2 = 35.8;                           // Pulley diameter at arm shaft
float conv_incr_thetas = (D_POLIA_2 / D_POLIA_1); // Conversion to 1° due to arm pulleys
float conv_incr_z = 45;                           // Conversion from 1 mm to 1° due to the spindle

// float L1 = 248; // Arm 1 size in mm
// float L2 = 290; // Arm 2 size in mm

float poseX = 0;
float poseY = 0;
float poseZ = 0;

float Xmax = 221;
float Ymax = 221;
float Zmax = 151;

float poseatX = 0;
float poseatY = 0;
float poseatZ = 0;

void initMotors()
{
    stepperX.begin(MOTOR_X_RPM, MICROSTEPS_X);
    stepperY.begin(MOTOR_Y_RPM, MICROSTEPS_Y);
    stepperZ.begin(MOTOR_Z_RPM, MICROSTEPS_Z);
    // Configuração de aceleração e desaceleração do motores
    stepperX.setSpeedProfile(stepperX.LINEAR_SPEED, MOTOR_ACCEL_THETA1, MOTOR_DECEL_THETA1);
    stepperY.setSpeedProfile(stepperY.LINEAR_SPEED, MOTOR_ACCEL_THETA2, MOTOR_DECEL_THETA2);
    stepperZ.setSpeedProfile(stepperZ.LINEAR_SPEED, MOTOR_ACCEL_Z, MOTOR_DECEL_Z);

    pinMode(STEP_X, OUTPUT);
    pinMode(DIR_X, OUTPUT);
    pinMode(EN_X, OUTPUT);
    pinMode(STEP_Y, OUTPUT);
    pinMode(DIR_Y, OUTPUT);
    pinMode(EN_Y, OUTPUT);
    pinMode(STEP_Z, OUTPUT);
    pinMode(DIR_Z, OUTPUT);
    pinMode(EN_Z, OUTPUT);

    pinMode(SensorX, INPUT);
    pinMode(SensorY, INPUT);
    pinMode(SensorZ, INPUT);

    digitalWrite(EN_X, LOW);
    digitalWrite(EN_Y, LOW);
    digitalWrite(EN_Z, LOW);
}

void homing()
{

    bool sx = 0;
    bool sy = 0;
    bool sz = 0;

    float incrX_home = -1;
    float incrY_home = -1;
    float incrZ_home = -1;

    stepperX.begin(1, MICROSTEPS_X);
    stepperY.begin(1, MICROSTEPS_Y);
    stepperZ.begin(1, MICROSTEPS_Z);

    while (sx == 0 || sy == 0 || sz == 0)
    {
        sx = digitalRead(SensorX);
        sy = digitalRead(SensorY);
        sz = digitalRead(SensorZ);

        if (sx == 1)
        {
            poseX = 0;
            incrX_home = 0;
        }
        else
        {
            incrX_home = -1;
        }

        if (sy == 1)
        {
            incrY_home = 0;
        }
        else
        {
            incrY_home = -1;
        }

        if (sz == 1)
        {
            incrZ_home = 0;
        }
        else
        {
            incrZ_home = -1;
        }

        stepperX.rotate(incrX_home);
        stepperY.rotate(incrY_home);
        stepperZ.rotate(incrZ_home);

        controller.rotate(incrX_home, incrY_home, incrZ_home);
        delay(5);
    }

    poseX = 0;
    poseY = 0;
    poseZ = 0;

    stepperX.begin(MOTOR_X_RPM, MICROSTEPS_X);
    stepperY.begin(MOTOR_Y_RPM, MICROSTEPS_Y);
    stepperZ.begin(MOTOR_Z_RPM, MICROSTEPS_Z);
}

void homing2()
{
    bool sx = 0;
    bool sy = 0;
    bool sz = 0;

    float incrX_home = -1;
    float incrY_home = -0.5;
    float incrZ_home = -1;

    stepperX.begin(10, MICROSTEPS_X);
    stepperY.begin(20, MICROSTEPS_Y);
    stepperZ.begin(100, MICROSTEPS_Z);

    while (sx == 0 || sy == 0 || sz == 0)
    {
        sx = digitalRead(SensorX);
        sy = digitalRead(SensorY);
        sz = digitalRead(SensorZ);

        for (int i = 0; i < 10; i++)
        {
            sx = digitalRead(SensorX);
            while (sx == 0)
            {
                sx = digitalRead(SensorX);
                if (sx == 1)
                {
                    incrX_home = 0;
                }
                else
                {
                    incrX_home = -1;
                }
                stepperX.rotate(incrX_home);
                stepperY.rotate(0);
                stepperZ.rotate(0);
                // controller.rotate(incrX_home, 0, 0);
                // delay(5);
            }
            delay(50);
        }

        for (int i = 0; i < 10; i++)
        {
            sy = digitalRead(SensorY);
            while (sy == 0)
            {
                sy = digitalRead(SensorY);
                if (sy == 1)
                {
                    incrY_home = 0;
                }
                else
                {
                    incrY_home = -0.5;
                }
                stepperX.rotate(0);
                stepperY.rotate(incrY_home);
                stepperZ.rotate(0);
                // controller.rotate(incrX_home, 0, 0);
                // delay(5);
            }
            delay(50);
        }

        for (int i = 0; i < 10; i++)
        {
            sz = digitalRead(SensorZ);
            while (sz == 0)
            {
                sz = digitalRead(SensorZ);
                if (sz == 1)
                {
                    incrZ_home = 0;
                }
                else
                {
                    incrZ_home = -1;
                }
                stepperX.rotate(0);
                stepperY.rotate(0);
                stepperZ.rotate(incrZ_home);
                // controller.rotate(incrX_home, 0, 0);
                // delay(5);
            }
            delay(50);
        }

        delay(10);
    }
    poseX = 0;
    poseY = 0;
    poseZ = 0;

    stepperX.begin(MOTOR_X_RPM, MICROSTEPS_X);
    stepperY.begin(MOTOR_Y_RPM, MICROSTEPS_Y);
    stepperZ.begin(MOTOR_Z_RPM, MICROSTEPS_Z);
}

void motorRun(float x, float y, float z, float velx, float vely, float velz)
{
    // Serial.print("incrmento: ");
    // Serial.println(conv_incr_thetas);

    stepperX.begin(velx, MICROSTEPS_X);
    stepperY.begin(vely, MICROSTEPS_Y);
    stepperZ.begin(velz, MICROSTEPS_Z);

    float dfx = 0;
    float dfz = 0;
    float dfy = 0;

    if (x <= Xmax and x >= 0 and poseX > 0 and x != 0)
    {
        dfx = poseX - x;
        dfx = dfx * -1;
        poseX = poseX + dfx;
    }
    if (poseX == 0 and x <= Xmax)
    {
        dfx = poseX + x;
        poseX = poseX + dfx;
    }

    if (y <= Ymax and y >= 0 and poseY > 0 and y != 0)
    {
        dfy = poseY - y;
        dfy = dfy * -1;
        poseY = poseY + dfy;
    }
    if (poseY == 0 and y <= Ymax)
    {
        dfy = poseY + y;
        poseY = poseY + dfy;
    }

    if (z <= Zmax and z >= 0 and poseZ > 0 and z != 0)
    {
        dfz = poseZ - z;
        dfz = dfz * -1;
        poseZ = poseZ + dfz;
    }
    if (poseZ == 0 and z <= Zmax)
    {
        dfz = poseZ + z;
        poseZ = poseZ + dfz;
    }

    float x2 = (dfx * conv_incr_thetas);
    float y2 = (dfy * conv_incr_thetas);
    float z2 = (dfz * 45.0);

    // Serial.println("motor run");
    // Serial.println("<---------------->");
    // Serial.println(x2);
    // Serial.println(y2);
    // Serial.println(z2);
    // Serial.println("<---------------->");
    // Serial.println(int(x2));
    // Serial.println(int(y2));
    // Serial.println(int(z2));
    controller.rotate(x2, y2, z2);
}

void motorRunIncrement(float x, float y, float z)
{
    // stepperX.begin(MOTOR_X_RPM, MICROSTEPS_X);
    // stepperY.begin(MOTOR_Y_RPM, MICROSTEPS_Y);
    // stepperZ.begin(MOTOR_Z_RPM, MICROSTEPS_Z);

    // stepperX.begin(1, MICROSTEPS_X);
    // stepperY.begin(1, MICROSTEPS_Y);
    // stepperZ.begin(1, MICROSTEPS_Z);

    stepperX.begin(1, MICROSTEPS_X);
    stepperY.begin(1, MICROSTEPS_Y);
    stepperZ.begin(100, MICROSTEPS_Z);

    poseatX = poseX;
    poseatY = poseY;
    poseatZ = poseZ;

    float dfx = 0;
    float dfz = 0;
    float dfy = 0;

    if (poseX + x < Xmax and poseX + x >= 0)
    {
        poseX = poseX + x;
        dfx = poseX - poseatX;
    }
    if (poseY + y < Ymax and poseY + y >= 0)
    {
        poseY = poseY + y;
        dfy = poseY - poseatY;
    }
    if (poseZ + z < Zmax and poseZ + z >= 0)
    {
        poseZ = poseZ + z;
        dfz = poseZ - poseatZ;
    }
    float x2 = (dfx * conv_incr_thetas);
    float y2 = (dfy * conv_incr_thetas);
    float z2 = (dfz * 45.0);
    // Serial.println("motor run");
    // Serial.println("<---------------->");
    // Serial.println(x2);
    // Serial.println(y2);
    // Serial.println(z2);
    // Serial.println("<---------------->");
    // Serial.println(int(x2));
    // Serial.println(int(y2));
    // Serial.println(int(z2));
    controller.rotate(x2, y2, z2);

    stepperX.begin(MOTOR_X_RPM, MICROSTEPS_X);
    stepperY.begin(MOTOR_Y_RPM, MICROSTEPS_Y);
    stepperZ.begin(MOTOR_Z_RPM, MICROSTEPS_Z);
}

float returnPoseX()
{
    return poseX;
}

float returnPoseY()
{
    return poseY;
}

float returnPoseZ()
{
    return poseZ;
}