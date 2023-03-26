String configCode = "This will not be matched!";
final char OUTER_KEY = '#';
int numGraphs;
boolean configured = false;

void serialEvent( Serial ser )
{
    // Listen for serial data until #, the end of transmission key
    try
    {
  String message = ser.readStringUntil( OUTER_KEY );
  if ( message == null || message.isEmpty() || message.equals( OUTER_KEY ) )
  {
      return;
  }

  JSONObject json = parseJSONObject( message );

  if ( json == null )
  {
      return;
  }    
   if ( json.hasKey( "ng" ) || json.hasKey( "lu" ) )
  {
    return;
  }
output(11, message);  
  // ********************************************************* //
  // ************* PLOT SETUP FROM CONFIG CODE *************** //
  // ********************************************************* //

  String tempCode = "";
  boolean config = false;
  
  
 
 
      // Matching a code means we have configured correctly
      configured = true;
          
      // *********************************************************** //
      // ************ NORMAL PLOTTING FUNCTIONALITY **************** //
      // *********************************************************** //
      int tempTime = json.getInt( "t" );
      
      JSONArray jsonGraphs = json.getJSONArray( "g" );
     numGraphs=6;
      for ( int i = 0; i < numGraphs; i++ )
      {
    JSONArray data = jsonGraphs.getJSONObject( 0 ).getJSONArray( "d" );

    double[] tempData = new double[ data.size() ];

    // Update graph objects with new data
    print("Axes [");
    for ( int j = 0; j < data.size(); j++ )
    {
        tempData[j] = data.getDouble( j );
      print(tempData[j]);if(j!=(data.size()-1))print(";");
    }
      print("] ");
  //  graphs.get( i ).Update( tempData, tempTime );
  if(data.getDouble( 1 )!=0)RotAxe1=(-PI/180)*(float)(data.getDouble( 1 )-260);
  if(data.getDouble( 2 )!=0)RotAxe2=(PI/180)*(float)(data.getDouble( 2 )-286);
  print (RotAxe1*180/PI+"|"+RotAxe2*180/PI);
   println("]");
      }     
    }
    catch ( Exception e )
    {
  //logMessage( "Exception in serialEvent: " + e.toString(), true );
    }
}
