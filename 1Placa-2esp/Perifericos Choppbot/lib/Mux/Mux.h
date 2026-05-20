#ifndef MUX_H
#define MUX_H

bool muxReturnOut(int pin);
bool muxReturnIn(int pin);
void muxOut(int pin, bool state);
void muxInit();
void muxRun();
void muxShowData();

#endif