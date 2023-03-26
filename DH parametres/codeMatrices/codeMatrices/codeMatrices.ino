#include <MatrixMath.h>


#define N  (4)

mtx_type A[N][N];
mtx_type B[N][N];
mtx_type C[N][N];
mtx_type v[N];      // This is a row vector
mtx_type w[N];

mtx_type maxVal = 10;  // maxValimum random matrix entry range

void setup()
{
	Serial.begin(115200);

	// Initialize matrices
  float tt=0;
	for (int i = 0; i < N; i++)
	{
		v[i] = i + 1;                  // vector of sequential numbers
		for (int j = 0; j < N; j++)
		{
			A[i][j] = tt; //float(random(1000*maxVal))/1000 - maxVal / 2.0f; // A is random
      tt=tt+1;
			if (i == j)
			{
				B[i][j] = 1.0f;                  // B is identity
			}
			else
			{
				B[i][j] = 0.0f;
			}
		}
	}

}

void loop()
{

	Matrix.Multiply((mtx_type*)A, (mtx_type*)B, N, N, N, (mtx_type*)C);

  Serial.println("//////////////////////////////////////////////////");
  Serial.println("After multiplying C = A*B:");
	Matrix.Print((mtx_type*)A, N, N, "A");

	Matrix.Print((mtx_type*)B, N, N, "B");
	Matrix.Print((mtx_type*)C, N, N, "C");
	Matrix.Print((mtx_type*)v, N, 1, "v");

	Matrix.Add((mtx_type*) B, (mtx_type*) C, N, N, (mtx_type*) C);
  Serial.println("//////////////////////////////////////////////////");
	Serial.println("// C = B+C (addition in-place)");
	Matrix.Print((mtx_type*)C, N, N, "C");
	Matrix.Print((mtx_type*)B, N, N, "B");

	Matrix.Copy((mtx_type*)A, N, N, (mtx_type*)B);
  Serial.println("//////////////////////////////////////////////////");
	Serial.println("// Copied A to B:");
	Matrix.Print((mtx_type*)B, N, N, "B");

	Matrix.Invert((mtx_type*)A, N);
  Serial.println("//////////////////////////////////////////////////");
	Serial.println("// Inverted A:");
	Matrix.Print((mtx_type*)A, N, N, "A");

	Matrix.Multiply((mtx_type*)A, (mtx_type*)B, N, N, N, (mtx_type*)C);
  Serial.println("//////////////////////////////////////////////////");
	Serial.println("// C = A*B");
	Matrix.Print((mtx_type*)C, N, N, "C");

	// Because the library uses pointers and DIY indexing,
	// a 1D vector can be smoothly handled as either a row or col vector
	// depending on the dimensions we specify when calling a function
	Matrix.Multiply((mtx_type*)C, (mtx_type*)v, N, N, 1, (mtx_type*)w);
  Serial.println("//////////////////////////////////////////////////");
	Serial.println("// C*v = w:");
	Matrix.Print((mtx_type*)v, N, 1, "C");
	Matrix.Print((mtx_type*)w, N, 1, "w");

  Matrix.Multiply((mtx_type*)A, (mtx_type*)v, N, N, 1, (mtx_type*)w);
  Serial.println("//////////////////////////////////////////////////");
  Serial.println("// A*v = w:");
  Matrix.Print((mtx_type*)v, N, 1, "v");
  Matrix.Print((mtx_type*)w, N, 1, "w");



  DH();
	while(1);
}



mtx_type L[4][4];
mtx_type M[4][4];


void DH(){
//  T = | 00 ; 01 ; 02 ; 03 |  (ij)
//      | 10 ; 11 ; 12 ; 13 |
//      | 20 ; 21 ; 22 ; 23 | 
//      | 30 ; 31 ; 32 ; 33 |

// DH 
//     ___________________________________ 
//    |   a    | alpha  |   d    | theta  |
// 1  |   0    |   -90  |   1    |   45   |
// 2  |   0    |     0  |   1    |   30   |
long tt=millis();
double a1=0,alpha1=-90*PI/180,d1=1,theta1=45*PI/180;
mtx_type t[4][4]= {{cos(theta1), -sin(theta1) * cos(alpha1), sin(theta1) * sin(alpha1), a1 * cos(theta1)},
                   {sin(theta1),  cos(theta1) * cos(alpha1),-cos(theta1) * sin(alpha1), a1 * sin(theta1)},
                   {          0,                sin(alpha1),               cos(alpha1),               d1},
                   {          0,                          0,                         0,                1}};
Serial.print("Time1: ");Serial.println (millis()-tt);
Matrix.Print((mtx_type*)t, 4, 4, "t");
Serial.print("Time2: ");Serial.println (millis()-tt);

}
