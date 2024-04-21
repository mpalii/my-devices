#ifndef BUTTON_MATRIX_H_
#define BUTTON_MATRIX_H_

#include "led_matrix.h"

void handle_input_in_evaluation_mode(void);
void handle_input(sign *user_sign);
bool handle_pvm_input(sign *user_sign);

#endif /* BUTTON_MATRIX_H_ */