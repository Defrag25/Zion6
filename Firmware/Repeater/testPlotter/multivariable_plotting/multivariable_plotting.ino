/*
  ===========================================================================================
  Example to demonstrate multi-variable plotting against time
  -------------------------------------------------------------------------------------------
  Plotter
  v2.4.1
  https://github.com/devinaconley/arduino-plotter
  by Devin Conley
  ===========================================================================================
*/

#include "Plotter.h"

// Plotted variables must be declared as globals 
double Ax1;
double Ax2;
double Ax3;
double Ax4;
double Ax5;
double Ax6;

// Also declare plotter as global
Plotter p;

void setup()
{
    // Start plotter
    p.Begin();
  
    // Add 5 variable time graph
    p.AddTimeGraph( "Zion6", 1000, "Axe1", Ax1, "Axe2", Ax2, "Axe3", Ax3,  "Axe4", Ax4, "Axe5", Ax5 , "Axe6", Ax6 );
}

void loop()
{
    // Update variables with arbitrary sine/cosine data
    Ax1 = 3*cos( 2.0*PI*( millis()/2500.0 ) );
    Ax2 = 4.0;
    Ax3 = 10*sin( 2.0*PI*( millis() / 5000.0 ) );
    Ax4 = 7*cos( 2.0*PI*( millis() / 5000.0 ) );
    Ax5 = 5*sin( 2.0*PI*( millis() / 5000.0 ) );
    Ax6 = Ax6 +0.01; if (Ax6>5)Ax6=0;

    // Plot
    p.Plot();
}
