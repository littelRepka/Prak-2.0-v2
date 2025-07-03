#include<math.h>
double clak( double S, double t , double r){
     return pow(1 + (r/100), t)*S;
}