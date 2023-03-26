import java.util.StringTokenizer;  
HashMap<String, Float> variables = new HashMap<String, Float>();

final int EXPR_VALUE  = 1;
final int EXPR_LPAREN = 2;
final int EXPR_RPAREN = 3;
final int EXPR_OP     = 4;

// ------------------------------------------------------------------------ //
void setup()
{
  size( 400, 400 );
  noLoop();
  
  // Simple expression evaluation:
  String expr = "1 + (10.5 + 5) /2";
  println( expr + " = " + Evaluate(expr) );
  
  background(255);
  
  // Draw the axis
  stroke(0);
  line(0,height/2,width,height/2);
  line(width/2,0,width/2,height);
  
  // Plot some expressions
  strokeWeight(2);
  stroke( 255,0,0 );
  PlotExpression( " x ^ 3" );
  
  stroke( 0,255,0 );
  PlotExpression( "2*x + 4" );
  
  stroke( 0,0,255 );
  PlotExpression( "x^(1/2)" );
    stroke( 100,100,100 );
    int x;
    for(x=0 ; x<10;x++){
      
 // PlotExpression( "sin( x )" );
 //Evaluate("sin( x )");
    }
}

// ------------------------------------------------------------------------ //
void PlotExpression( String expression )
{
  float previousY = width/2;
  for( int i=0; i<width; ++i )
  {
    SetValue( "x", map( i, 0, width, -10, 10 ) );
    
    float y = map( Evaluate( expression ), -10, 10, 0, height );
    line( i, y, i-1, previousY );
    previousY = y;    
  }    
}

// ------------------------------------------------------------------------ //
protected float Evaluate( String strExpression )
{
  return Evaluate( new StringTokenizer( strExpression.toLowerCase() ) );    
}

// ------------------------------------------------------------------------ //
protected float Evaluate( StringTokenizer st )
{
  // Let's get all the tokens into an array
  int       nTokens   = st.countTokens();
  int       nTok      = 0;
  String [] strTokens = new String[nTokens];
  char   [] Chars     = { '(',')','+','*','/','%','^' };
  
  for( int i = 0; i <  nTokens; ++i )
  {
    String    strTok  = st.nextToken();
    String [] NewToks = SplitAtChars( Chars, strTok );
    
    if( NewToks != null )
    {
      strTokens = expand( strTokens, strTokens.length + NewToks.length - 1 );
      for( int k=0; k < NewToks.length; ++k )
        strTokens[nTok++] = NewToks[k];
    }
    else
      strTokens[nTok++] = strTok;
  }

  return EvaluateExpr( strTokens );
}

// ------------------------------------------------------------------------ //
protected float GetValue( String name )
{
  if( name.length() == 0 ) return 0;
  if( (name.charAt(0) >= '0' && name.charAt(0) <= '9') ||
      name.charAt(0) == '.' )
  {
    float  value = 0;
    try  { value = Float.valueOf( name ); } catch ( Exception e ) {}
    return value;
  }
  
  if( variables.containsKey(name) )
    return variables.get(name); // Auto-unboxed
    
  return 0;
}

// ------------------------------------------------------------------------ //
protected void SetValue( String name, float value )
{
  variables.put( name, value );
}

// ------------------------------------------------------------------------ //
protected boolean ExprIsOp( char op )
{
  return op == '+' || op == '-' || op == '*' || op == '/' || op == '%' || op == '^';
}

// ------------------------------------------------------------------------ //
protected float ExprOperation( float v0, String strOp, float v1 )
{
  if( strOp == null )
    return 0.f;
    
  char op = strOp.charAt(0);
  switch( op )
  {
    case '+': return v0 + v1;
    case '-': return v0 - v1;
    case '*': return v0 * v1;
    case '/': return v0 / v1;
    case '%': return v0 % v1;
    case '^': return pow(v0, v1);
  }
  return 0.f;
}

// ------------------------------------------------------------------------ //
protected int GetExprTokenType( String strToken )
{
  if( strToken.length() == 1 )
  {
         if( strToken.charAt(0) == '('    ) return EXPR_LPAREN;
    else if( strToken.charAt(0) == ')'    ) return EXPR_RPAREN;
    else if( ExprIsOp(strToken.charAt(0)) ) return EXPR_OP;
  }
  return EXPR_VALUE;
}

// ------------------------------------------------------------------------ //
protected int FindMatchingParen( String [] strTokens )
{
  int nParen = 1;
  for( int i=1; i < strTokens.length; ++i )
  {
    if( strTokens[i] == null || strTokens[i].length() != 1 )
      continue;
    
         if( strTokens[i].charAt(0) == '(' ) ++nParen;
    else if( strTokens[i].charAt(0) == ')' ) --nParen;
    
    if( nParen == 0 )
      return i;
  }
  return strTokens.length;
}

// ------------------------------------------------------------------------ //
protected float EvaluateExpr( String [] strTokens )
{    
       if( strTokens.length == 1 ) return GetValue( strTokens[0] );
  else if( strTokens.length == 2 ) return 0.f;
  else if( strTokens.length == 3 )
  {
    return ExprOperation( GetValue( strTokens[0] ), strTokens[1], GetValue( strTokens[2] ) );
  }
  else if( strTokens.length > 3  )
  {
    int nType = GetExprTokenType( strTokens[0] );
    if( nType == EXPR_LPAREN )
    {
      int nIndex = FindMatchingParen( strTokens );
      
      // If we couldn't find it then return, incomplete expression
      if( nIndex == strTokens.length )
        return 0;
      
      // If the matching parenthesis is the last token, then the expression is just inside
      if( nIndex == strTokens.length - 1 )
      {
        return EvaluateExpr( subset( strTokens, 1, nIndex - 1 ) );
      }
      else
      {
        int nOpIndex    = nIndex   + 1;
        int nRightIndex = nOpIndex + 1;
        
        // Compute the left side
        float left = EvaluateExpr( subset( strTokens, 1, nIndex - 1 ) );
        
        // Compute the right side
        float right = EvaluateExpr( subset( strTokens, nRightIndex, strTokens.length - nRightIndex ) );
        
        // Return the result
        return ExprOperation( left, strTokens[nOpIndex], right );
      }
    }
    else if( nType == EXPR_VALUE ) // Value
    {
      float v1 = GetValue( strTokens[0] );
      float v2 = EvaluateExpr( subset( strTokens, 2, strTokens.length - 2 ) );
      return ExprOperation( v1, strTokens[1], v2 );
    }
  }
  
  return 0.f;
}

// ------------------------------------------------------------------------ //
String [] SplitAtChars( char[] ch, String strTok )
{
  // Don't return anything if the token's only a char
  if( strTok.length() <= 1 )
    return null;
    
  // Don't return anything if we don't have anything to split
  boolean bFound = false;
  for( int i=0; i < ch.length; ++i )
    if( strTok.indexOf(ch[i]) >= 0 )
    {
      bFound = true;
      break;
    }
    
  if( !bFound ) return null;

  // Split up the string
  int       nChrIndex = 0;
  int       nTok      = 0;
  int       nDone     = strTok.length();
  String [] ret       = new String[1];
  
  for(;;)
  { 
    int i=0;
    nChrIndex = -1;
    for( ; i < ch.length && nChrIndex == -1; ++i )
      nChrIndex = strTok.indexOf(ch[i]);
    if( nChrIndex == -1 )
    {
      ret[nTok++] = strTok;
      break;
    }
    --i;
    for( ; i < ch.length; ++i )
    {
      int nNewIndex = strTok.indexOf(ch[i], 0);
      if( nNewIndex == -1 ) nNewIndex = nDone;
      nChrIndex = min( nChrIndex, nNewIndex );
    }

    int nLen = strTok.length();
    if( nLen > 1 )
    {
      ret = expand( ret, ret.length + 3 );
      if( nChrIndex == 0 )
        nChrIndex = 1;

      ret[nTok++]   = strTok.substring(0, nChrIndex);
      strTok        = strTok.substring(nChrIndex);
    }
    else
    {
      ret[nTok++]   = strTok;
      break;
    }
  }

  return subset( ret, 0, nTok );
}
