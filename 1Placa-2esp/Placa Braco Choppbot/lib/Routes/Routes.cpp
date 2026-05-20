#include <ArduinoJson.h>
#include <StepMotor.h>
#include <WebServer.h>
#include <Choppbot.h>
#include <Arduino.h>
#include <Routes.h>
#include <WiFi.h>
#include <Grab.h>
#include <Cup.h>

WebServer server(80);
StaticJsonDocument<300> document;
char buffer[300];

void routesCreates()
{

    server.on(cupTest, HTTP_POST, cup_Test);
    server.on(cupService, HTTP_POST, cup_Service);
    server.on(cupWrite, HTTP_POST, cup_Write);

    server.on(grabWrite, HTTP_POST, triggerGrab);
    server.on(grabBye, HTTP_POST, byegrab);

    server.on(positionRun, HTTP_POST, moveRobot);
    server.on(positionRunIncrement, HTTP_POST, moveIncrement);
    server.on(positionHome, home);
    server.on(returnpose, returnPosition);

    server.begin();
}

void serverRun()
{
    server.handleClient();
}

void moveRobot()
{
    String body = server.arg("plain");
    deserializeJson(document, body);
    motorRun(document["x"], document["y"], document["z"], document["vx"], document["vy"], document["vz"]);
    createJson();
    server.send(200, "application/json", buffer);
}

void moveIncrement()
{
    String body = server.arg("plain");
    deserializeJson(document, body);
    motorRunIncrement(document["x"], document["y"], document["z"]);
    createJson();
    server.send(200, "application/json", buffer);
}

void returnPosition()
{
    createJson();
    server.send(200, "application/json", buffer);
}

void home()
{
    homing2();
    createJson();
    server.send(200, "application/json", buffer);
}

void createJson()
{
    document.clear();
    JsonObject robot = document.createNestedObject("robot");
    robot["x"] = returnPoseX();
    robot["y"] = returnPoseY();
    robot["z"] = returnPoseZ();
    serializeJson(document, buffer);
}

void cup_Test()
{
    String body = server.arg("plain");
    deserializeJson(document, body);
    testCup(document["min"], document["max"]);
    document.clear();
    document["result"] = "success";
    serializeJson(document, buffer);
    server.send(200, "application/json", buffer);
}

void cup_Service()
{
    String body = server.arg("plain");
    deserializeJson(document, body);
    serviceCup(document["min"], document["max"], 1);
    document.clear();
    document["result"] = "success";
    serializeJson(document, buffer);
    server.send(200, "application/json", buffer);
}

void cup_Write()
{
    String body = server.arg("plain");
    deserializeJson(document, body);
    writeCup(document["angle"]);
    document.clear();
    document["result"] = "success";
    serializeJson(document, buffer);
    server.send(200, "application/json", buffer);
}

void byegrab()
{
    if (server.hasArg("plain") == false)
    {
        // handle error here
    }
    String body = server.arg("plain");
    deserializeJson(document, body);
    byebye(document["min"], document["max"], document["cycles"], document["home"]);
    document.clear();
    document["result"] = "success";
    document["pose"] = returnPoesgrab();
    serializeJson(document, buffer);
    server.send(200, "application/json", buffer);
}

void triggerGrab()
{
    String body = server.arg("plain");
    deserializeJson(document, body);
    triggergrab(document["angle"]);
    document.clear();
    document["result"] = "success";
    document["pose"] = returnPoesgrab();
    serializeJson(document, buffer);
    server.send(200, "application/json", buffer);
}