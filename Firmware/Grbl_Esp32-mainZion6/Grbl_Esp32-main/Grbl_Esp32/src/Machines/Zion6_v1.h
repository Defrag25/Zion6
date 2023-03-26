#pragma once
// clang-format off

/*
    Zion6_v1.h

  

    Part of Grbl_ESP32
    Pin assignments for the ESP32 6-axis board
  
  
    Grbl_ESP32 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    Grbl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with Grbl_ESP32.  If not, see <http://www.gnu.org/licenses/>.
*/
#define MACHINE_NAME            "Zion6 V1.0"

#define N_AXIS 6
//#define DEFAULT_STEPPER
// === Special Features

// Motor X
#define X_STEP_PIN              GPIO_NUM_36
#define X_DIRECTION_PIN         GPIO_NUM_39
#define X_DISABLE_PIN           GPIO_NUM_34
// Motor Y
#define Y_STEP_PIN              GPIO_NUM_32
#define Y_DIRECTION_PIN         GPIO_NUM_33
#define Y_DISABLE_PIN           GPIO_NUM_34
// Motor Z
#define Z_STEP_PIN              GPIO_NUM_27
#define Z_DIRECTION_PIN         GPIO_NUM_14
#define Z_DISABLE_PIN           GPIO_NUM_34
// Motor A
#define A_STEP_PIN              GPIO_NUM_23
#define A_DIRECTION_PIN         GPIO_NUM_22 
#define A_DISABLE_PIN           GPIO_NUM_34
// Motor B
#define B_STEP_PIN              GPIO_NUM_21
#define B_DIRECTION_PIN         GPIO_NUM_19 
#define B_DISABLE_PIN           GPIO_NUM_34
// Motor C
#define C_STEP_PIN              GPIO_NUM_17 
#define C_DIRECTION_PIN         GPIO_NUM_16 
#define C_DISABLE_PIN           GPIO_NUM_34



#define X_LIMIT_PIN             GPIO_NUM_35
#define Y_LIMIT_PIN             GPIO_NUM_26
#define Z_LIMIT_PIN             GPIO_NUM_13
#define A_LIMIT_PIN             GPIO_NUM_3
#define B_LIMIT_PIN             GPIO_NUM_5
#define C_LIMIT_PIN             GPIO_NUM_2
#define PROBE_PIN               GPIO_NUM_15

//#define DEFAULT_INVERT_LIMIT_PINS       0
//#define DEFAULT_INVERT_PROBE_PIN        0


// 5V output CNC module in socket #3
// https://github.com/bdring/6-Pack_CNC_Controller/wiki/4x-5V-Buffered-Output-Module
//#define SPINDLE_TYPE            SpindleType::PWM
//#define SPINDLE_OUTPUT_PIN      GPIO_NUM_4
//#define SPINDLE_ENABLE_PIN      GPIO_NUM_4
//#define SPINDLE_DIR_PIN         GPIO_NUM_16
//#define COOLANT_MIST_PIN        GPIO_NUM_27

// === Default settings
//#define DEFAULT_STEP_PULSE_MICROSECONDS 2 //I2S_OUT_USEC_PER_PULSE


