#ifndef CHOPPBOT_H
#define CHOPPBOT_H
// definição de pinos da maquina
#define SolenoideA 1
#define SolenoideB 2

#define FluxA 4
#define FluxB 5

#define Giroled1 7
#define Giroled2 8

#define SensorGarra1 7
#define SensorGarra2 8
#define SensorDispenser 6

#define SX 1
#define SY 2
#define SZ 3

#define LedStatus 2

// definição pinos esp
#define Backup_in 35
#define Backup_out 18

#define Servo1 15
#define Servo2 02
#define Servo3 04
#define Servo4 05

#define Temp 32

#define SensorX 39
#define SensorY 36
#define SensorZ 34

#define gas 3

// definiçaõ pino do esp para controle dos motores
#define STEP_X 12
#define DIR_X 13
#define EN_X 26

#define STEP_Y 27
#define DIR_Y 14
#define EN_Y 26

#define STEP_Z 33
#define DIR_Z 25
#define EN_Z 26

#define STEP_W 23
#define DIR_W 19
#define EN_W 26

// definição de parametros para controle dos motores

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define MOTOR_X_RPM 400 // Target RPM for X axis motor
#define MOTOR_Y_RPM 400 // Target RPM for Y axis motor
#define MOTOR_Z_RPM 400 // Target RPM for Z axis motor

// Acceleration and deceleration values are always in FULL steps / s^2
#define MOTOR_ACCEL_THETA1 800 // 90 Quanto maior mais acelerado
#define MOTOR_DECEL_THETA1 600 // 90 Quanto menor mais desacelerado
#define MOTOR_ACCEL_THETA2 600 // 110
#define MOTOR_DECEL_THETA2 400 // 110
#define MOTOR_ACCEL_Z 6000     // 10000
#define MOTOR_DECEL_Z 6000     // 10000

// If microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step etc.
#define MICROSTEPS_X 16
#define MICROSTEPS_Y 16
#define MICROSTEPS_Z 16

//  definição dos pinos do multiplexador
#define MuxAdress1 0x20
#define MuxAdress2 0x21
#define MuxAdress3 0x22
#define MuxAdress4 0x23
#define MuxAdress5 0x24
#define MuxAdress6 0x25
#define MuxAdress7 0x26
#define MuxAdress8 0x27

#define SwitchSensor1 P10 // s1
#define SwitchSensor2 P11 // s2
#define SwitchSensor3 P12 // s3
#define SwitchSensor4 P13 // s4
#define SwitchSensor5 P14 // s5
#define SwitchSensor6 P15 // s6
#define SwitchSensor7 P16 // s7
#define SwitchSensor8 P17 // s8
#define SwitchRelay1 P00  // r1 --> solenoide chopeira 1
#define SwitchRelay2 P01  // r2 --> solenoide chopeira 2
#define SwitchRelay3 P02  // r3
#define SwitchRelay4 P03  // r4
#define SwitchRelay5 P04  // r5 --> bomba para gatorade chopeira 1
#define SwitchRelay6 P05  // r6 --> bomba para gatorade chopeira 2
#define SwitchRelay7 P06  // r7
#define SwitchRelay8 P07  // r8 --> rele para o giroled

// definição de rotas
#define returnBoard "/esp32/return"
// rotas controle da garra
#define grabWrite "/esp32/grab/write"
#define grabBye "/esp32/grab/byebye"
// definição de rotas torneira 1
#define beerAservice "/esp32/beerA/trigger"
// definição de rotas torneira 2
#define beerBservice "/esp32/beerB/trigger"
// definição de rotas copo
#define cupTest "/esp32/cup/test"
#define cupService "/esp32/cup/service"
#define cupWrite "/esp32/cup/write"
// definição de rota para o giroled
#define ledtrigger "/esp32/led/trigger"
// definição de rota para o gas
#define gastrigger "/esp32/gas/trigger"
//  definição de rede
#define Rede "Choppbot"
#define Senha "Zions@1417"
// #define Rede "100 sinal"
// #define Senha "paoquentinho"

#endif