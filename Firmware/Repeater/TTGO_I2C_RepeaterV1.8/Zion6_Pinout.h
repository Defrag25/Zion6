// TTGO Pinout
#pragma once
//
//
//                                                       __________________________________
//                                                      |               TTGO               |
//                                                      |                                  |
//                                               GND    |GND    ____________________    3V |   3V3
//                                               GND    |GND   |                    |   36 |   SVP    GPIO36    ADC0        
//                                                21    | 21   |                    |   37 |    37    GPIO37                
//                                                22    | 22   |      ST77898V      |   38 |    38    GPIO38                
//                   FDC_REF6                     17    | 17   |                    |   39 |   SVN    GPIO39    ADC3        
//                   PALPEUR     ADC12    GPIO2    2    |  2   |      135 x 240     |   32 |    32    GPIO32    ADC4        FDC_REF5
//                   TXD         ADC13   GPIO15   15    | 15   |                    |   33 |    33    GPIO33    ADC5        FDC_REF4
//                   Rxd         ADC14   GPIO13   13    | 13   |  (MOSI  19)        |   25 |    25    GPIO25   ADC18        FDC_REF3
//                               ADC15   GPIO12   12    | 12   |  (SCLK  18)        |   26 |    26    GPIO26   ADC19        FDC_REF2
//                                               GND    |GND   |  (  CS   5)        |   27 |    27    GPIO27   ADC17        FDC_REF1
//                                               GND    |GND   |  (  DC  16)        |  GND |   GND 
//                                               3V3    |3V3   |  ( RST  23)        |   5V |   5V  
//                                                      |      |  (  BL   4)        |      |
//                                                      |      |____________________|    --|
//                                                      |                               |BP|  Reset
//                                                      |                                --|
//                                                      |             ________             |
//                                                      |     BP0    |        |    BP35    |
//                                                      |      O     |  USB   |      O     | 
//                                                      |____________|   C    |____________|
//                                                                   |________|
//


#define FDC_REF1  27
#define FDC_REF2  26
#define FDC_REF3  25
#define FDC_REF4  33
#define FDC_REF5  32
#define FDC_REF6  17
#define PALPEUR    2



#define BP1_pin          0    // TTGO button
#define BP2_pin         35    // TTGO button
//#define LED_BUILTIN     34











 
