const int pwm_Resolution = 8;
const int pwm_MAX_DUTY_CYCLE = (int)(pow(2, pwm_Resolution) - 1);

const int pwm1Pin = 0;   //GPIO17      front   left
const int pwm2Pin = 17;   // GPIO16     back    left
const int pwm3Pin = 16;    // GPIO4      front   right
const int pwm4Pin = 4;    // GPIO0      back    right

const int pwm1Freq = 0; /* Hz */
const int pwm1Channel = 0;
const int pwm1Resolution = pwm_Resolution;

const int pwm2Freq = 0; /* Hz */
const int pwm2Channel = 2;
const int pwm2Resolution = pwm_Resolution;

const int pwm3Freq = 0; /* Hz */
const int pwm3Channel = 4;
const int pwm3Resolution = pwm_Resolution;

const int pwm4Freq = 0; /* Hz */
const int pwm4Channel = 6;
const int pwm4Resolution = pwm_Resolution;

