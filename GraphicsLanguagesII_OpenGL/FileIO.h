#include "common.h"

char* LoadFile(char* filename, int* filelength, bool addnullterminator)
{
    FILE* file;
    errno_t err = fopen_s( &file, filename, "rb" );

    char* buffer = 0;
    int length = 0;

    if( file )
    {
        fseek( file, 0, SEEK_END );
        long size = ftell( file );
        rewind( file );

        if( addnullterminator )
            buffer = new char[size+1];
        else
            buffer = new char[size];

        fread( buffer, size, 1, file );

        length = size;
        if( addnullterminator )
        {
            buffer[size] = 0;
            length += 1;
        }
        
        fclose( file );
    }

    *filelength = length;
    return buffer;
}