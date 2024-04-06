#ifndef MESSAGES_H_
#define MESSAGES_H_

#define TIMEOUT_SERIAL_PATTERN "%010lums-TIMEOUT\r\n"
#define TIMEOUT_LCD_MESSAGE "\r    Timeout!    \n  Try again...  "

#define RESULT_SERIAL_PATTERN "%010lums-RESULT\r\n"
#define RESULT_LCD_PATTERN "\rYour result is: \n%3ums           "

#define READY_SERIAL_PATTERN "%010lums-READY\r\n"
#define READY_LCD_PATTERN "\rBest result:    \n%3ums           "

#define WAIT_SERIAL_PATTERN "%010lums-WAIT: %ums\r\n"
#define WAIT_LCD_MESSAGE "\r      Wait      \n   for signal   "

#define MEASURING_SERIAL_PATTERN "%010lums-MEASURING\r\n"

#define FALSE_START_SERIAL_PATTERN "%010lums-FALSE START\r\n"
#define FALSE_START_LCD_MESSAGE "\r    Too fast    \n  try again...  "

#endif /* MESSAGES_H_ */