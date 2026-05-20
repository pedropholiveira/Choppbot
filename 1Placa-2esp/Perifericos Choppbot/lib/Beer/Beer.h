#ifndef BEER_H
#define BEER_H

void flux1(bool input);
void flux2(bool input);
float returnFlux(int valve);
void fluxRun(int pinflux1, int pinflux2);
void triggerFlux2(float copo, float time, float time2, bool state);
void triggerFlux1(float copo, float time, bool state, bool sangrar);
void triggerGas(float time, bool state);

#endif