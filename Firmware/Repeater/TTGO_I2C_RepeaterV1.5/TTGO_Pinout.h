// TTGO Pinout
#pragma once
//
//
//                                                       __________________________________
//                                                      |               TTGO               |
//                                                      |                                  |
//                                               GND    |GND    ____________________    3V |   3V3
//                                               GND    |GND   |                    |   36 |   SVP    GPIO36    ADC0        JOG_Speed0
//                        DRV_DirOutPin           21    | 21   |                    |   37 |    37    GPIO37                JOG_Speed1
//                        DRV_ClkOutPin           22    | 22   |      ST77898V      |   38 |    38    GPIO38                JOG_Axe1 
//              MACH3_ClkPin                      17    | 17   |                    |   39 |   SVN    GPIO39    ADC3        JOG_Axe0 
//              MACH3_DirPin     ADC12    GPIO2    2    |  2   |      135 x 240     |   32 |    32    GPIO32    ADC4        JOG_CodeurB
//              IHM_Codeur_B     ADC13   GPIO15   15    | 15   |                    |   33 |    33    GPIO33    ADC5        JOG_CodeurA
//              IHM_BP_Mode      ADC14   GPIO13   13    | 13   |  (MOSI  19)        |   25 |    25    GPIO29   ADC18        Mode_Pin       
//              IHM_Codeur_A     ADC15   GPIO12   12    | 12   |  (SCLK  18)        |   26 |    26    GPIO26   ADC19        CodeurX_B
//                                               GND    |GND   |  (  CS   5)        |   27 |    27    GPIO27   ADC17        CodeurX_A
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


#define CodeurX_A       26  // Regle numérique sur table ( 5µ )
#define CodeurX_B       27  // Regle numérique sur table ( 5µ )
#define MACH3_ClkPin    17  // Pulses provenant de MACH3
#define MACH3_DirPin     2  // Direction provenant de MACH3

#define Mode_Pin        25  // Entrée mode déplacement manuel
#define JOG_Speed0      36  // JOG SelectSpeed bit0
#define JOG_Speed1      37  // JOG SelectSpeed bit1
#define JOG_Axe0        39  // JOG SelectSpeed bit0
#define JOG_Axe1        38  // JOG SelectSpeed bit1
#define JOG_CodeurA     32  // JOG Encoder
#define JOG_CodeurB     33  // JOG Encoder



#define IHM_Codeur_A    15  // Codeur IHM
#define IHM_Codeur_B    12  // Codeur IHM
#define IHM_BP_Mode     13  // Bouton Encodeur ( pin à changer ) ****************************************************************** A REVOIR

#define DRV_ClkOutPin   22  // Pulse vers driver PAP
#define DRV_DirOutPin   21  // Direction vers driver PAP
  #define DRV_EnaOutPin   34  // Enable vers driver PAP
/*
#define Pot1            27    // ADC17  
#define Pot2            26    // ADC16  
*/
#define BP1_pin          0    // TTGO button
#define BP2_pin         35    // TTGO button
//#define LED_BUILTIN     34











 
