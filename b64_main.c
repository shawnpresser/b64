#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "b64.h"

void usage()
{
  printf("b64 {enc | dec} input\n");
}

static char*
grow_buffer( char* src, size_t srclen, size_t newsize )
{
  char* grow = calloc( 1, newsize );
  if ( srclen > newsize )
    srclen = newsize;
  memcpy( grow, src, srclen );
  free( src );
  return grow;
}

static char*
read_entire_file( FILE* fp, size_t* out_size )
{
  size_t size = 0;
  size_t max = 1024;
  char* buffer = calloc( 1, max );

  *out_size = 0;

  while ( fread( &buffer[size], 1, 1, fp ) )
  {
    ++size;
    if ( size >= max )
    {
      buffer = grow_buffer( buffer, max, 2*max );
      max *= 2;
    }
  }

  *out_size = size;
  return grow_buffer( buffer, max, size+1 );
}

int main( int argc, char** argv )
{
  FILE* infile = stdin;
  char* input = NULL;
  size_t inputlen = 0;
  int dec = 0;

  if ( argc < 2 )
  {
    usage();
    return 0;
  }

  if ( !strcmp( argv[1], "enc" ) )
    dec = 0;
  else if ( !strcmp( argv[1], "dec" ) )
    dec = 1;
  else
  {
    usage();
    return 0;
  }

  if ( argc >= 3 )
  {
    if ((infile = fopen(argv[2], "r")) == NULL)
    {
			warn("Cannot open input file: %s", argv[2]);
			exit(1);
    }
  }

  {
    size_t inputlen = 0;
    char* input = read_entire_file( infile, &inputlen );

    {
      char* out = calloc( 1, 2*inputlen );
      size_t len = 0;
      if ( dec )
        len = b64_decode( input, inputlen, out );
      else
        len = b64_encode( input, inputlen, out );
      {
        size_t i = 0;
        for ( ; i < len; i++ )
          fputc( out[ i ], stdout );
      }
      free( out );
    }
  }
  return 0;
}

