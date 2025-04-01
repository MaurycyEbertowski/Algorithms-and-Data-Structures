#include <stdio.h>
#include <stdarg.h>

int Printf( const char* sFormat, ... ); // ... - funkcja przyjmuje zmienna liczbe argumentow
int PrintfV( const char* sFormat, va_list arg );

void outDec( int );       // znakowo wypisuje liczbe calk
void outChar( char );     // wypisuje znak  // putchar()
void outStr( char* );     // wypisuje zanakowo string
void outDouble( double ); // wypisuje znakowow liczbe double    0.
void outNum( int x );     // wypisuje znakowo liczbe int >0     rekurencyjnie

int main( int argc, char* argv[] )
{
  int n = -0;
  char c = '$';
  double x = 12000000.34050000012;
  double y = -.12;
  double z = -0.5;
  char* str = (char*)"to jest string";

  Printf( "str: %s \n x= %f \n c= %c \n n=%d \\ % / \n y= %%f \n ` ` \n z=%f \n \%1abc", str, x, c, n, y, z );
  return 0;
}

int Printf( const char* sFormat, ... )
{
  va_list args; // Initialize variable arguments, declare a variable that can hold the variable argument list
  va_start( args, sFormat );
  int res = PrintfV( sFormat, args );
  va_end( args );// Reset variable arguments

  return res;
}

int PrintfV( const char* ptr, va_list args )
{
  char c;
  while( c = *ptr++ )
  {
    switch( c )
    {
    case '%':
      switch( c = *ptr++ ) {

      case 'd': outDec( va_arg( args, int ) ); break; // va_arg pozyskuje z va_list argument i automatycznie przechodzi do kolejnego
      case 'f': outDouble( va_arg( args, double ) ); break;
      case 's': outStr( va_arg( args, char* ) ); break;
      case 'c': outChar( va_arg( args, char ) ); break;
      default:
        outChar( '%' );
        if( c && c != '%' )
          outChar( c );
        else
          ptr--;
      }
      break;
    case '`':
      c = '\'';
    default:
      outChar( c );
    }
  }
  return 1;
}

void outChar( char c )
{
  putchar( c );
}

void outStr( char* pStr )
{
  while( *pStr ) {
    outChar( *pStr++ );
  }
}

void outDec( int x )
{
  if( x < 0 ) {
    outChar( '-' );
    x = -x;
  }
  else if( x == 0 ) {
    outChar( '0' );
    return;
  }
    outNum( x );
}

void outDouble( double x )
{
  if( x < 0 ) {
    x = -x;
    outChar( '-' );
  }
  outDec( (int)x );
  outChar( '.' );
  x -= (int)x;
  for( int i = 0; i < 7 && x - (int)x > 1e-5; i++ ) {
    x *= 10;
    outChar( (int)x % 10 + '0' );
  }

}

void outNum( int x )
{
  if( x > 0 ) {
    outNum( x / 10 );
    outChar( x % 10 + '0' );
  }
}
