#ifndef BACK_PROPAGATION_H
#define BACK_PROPAGATION_H

void back_prop_w(float out, float ideal, float w1[], float w2[], float w3[]);
void back_prop_b(float out, float ideal, float b1[], float b2[], float b3[]);

#endif
