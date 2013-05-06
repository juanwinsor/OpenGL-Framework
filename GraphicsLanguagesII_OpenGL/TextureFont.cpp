#include "common.h"
#include "TextureFont.h"
#include "FileIO.h"

TextureFont::TextureFont(char* filename)
{
	m_Initialized = false;

    m_ImageName[0] = 0;
    m_Chars = 0;
    m_KerningPairs = 0;
    m_NumChars = 0;
    m_NumKerningPairs = 0;

	//read in the font properties and character values
    int length;
    char* buffer = LoadFile( filename, &length, false );
    ReadFont( buffer, length );

	//load the bitmap with the fonts
	LoadFontImage();
}

TextureFont::~TextureFont()
{
	if( m_Chars )
        delete[] m_Chars;
    if( m_KerningPairs )
        delete[] m_KerningPairs;
}

void TextureFont::LoadFontImage()
{
	char tempfilename[MAX_PATH];
    sprintf_s(tempfilename, "Content/Fonts/%s", QueryImageName());
	m_FontTextureID = SOIL_load_OGL_texture( tempfilename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 
                                             SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y );
}

GLuint TextureFont::getFontTexture()
{
	return m_FontTextureID;
}

void TextureFont::ReadFont(char* filebuffer, unsigned int buffersize)
{
    //ErrorLog( "ReadFont - %d, %c%c%c%c\n", buffersize, filebuffer[0], filebuffer[1], filebuffer[2], filebuffer[3] );

    //assert( filebuffer[0] == 'B' );
    //assert( filebuffer[1] == 'M' );
    //assert( filebuffer[2] == 'F' );
    //assert( filebuffer[3] == 3 ); // This code only reads version 3 files... update it if using a newer BitmapFont format.

    char* fileptr = filebuffer + 4;

    while( fileptr < filebuffer + buffersize )
    {
        switch( fileptr[0] )
        {
        case 1: // Block type 1: info
            {
                fileptr += 1; // skip past the block type.
                unsigned int blocksize = *(unsigned int*)fileptr;
                fileptr += 4; // skip past size;
            
                // ignoring this block
                fileptr += blocksize;
            }
            break;

        case 2: //Block type 2: common
            {
                fileptr += 1; // skip past the block type.
                //unsigned int blocksize = *(unsigned int*)fileptr;
                fileptr += 4; // skip past size;

                m_Properties.lineHeight = *(unsigned short*)fileptr;
                fileptr += sizeof( m_Properties.lineHeight );

                m_Properties.base = *(unsigned short*)fileptr;
                fileptr += sizeof( m_Properties.base );

                m_Properties.scaleW = *(unsigned short*)fileptr;
                fileptr += sizeof( m_Properties.scaleW );

                m_Properties.scaleH = *(unsigned short*)fileptr;
                fileptr += sizeof( m_Properties.scaleH );

                m_Properties.pages = *(unsigned short*)fileptr;
                fileptr += sizeof( m_Properties.pages );

                unsigned char bitfields = *(unsigned char*)fileptr; // bits 0-6: reserved, bit 7: packed
                m_Properties.packed = (bitfields & 1<<7) > 0 ? true : false;
                fileptr += sizeof( bitfields );

                m_Properties.alphaChnl = *(unsigned char*)fileptr;
                fileptr += sizeof( m_Properties.alphaChnl );

                m_Properties.redChnl = *(unsigned char*)fileptr;
                fileptr += sizeof( m_Properties.redChnl );

                m_Properties.greenChnl = *(unsigned char*)fileptr;
                fileptr += sizeof( m_Properties.greenChnl );

                m_Properties.blueChnl = *(unsigned char*)fileptr;
                fileptr += sizeof( m_Properties.blueChnl );
            }
            break;

        case 3: // Block type 3: pages
            {
                fileptr += 1; // skip past the block type.
                unsigned int blocksize = *(unsigned int*)fileptr;
                fileptr += 4; // skip past size;
            
                // only readying the first file, ignoring others.
                strcpy_s( m_ImageName, MAX_PATH, fileptr );
                fileptr += blocksize;
            }
            break;

        case 4: // Block type 4: chars
            {
                fileptr += 1; // skip past the block type.
                unsigned int blocksize = *(unsigned int*)fileptr;
                fileptr += 4; // skip past size;

                m_NumChars = blocksize / 20;

                m_Chars = new CharDescriptor[m_NumChars];

                for( unsigned int i=0; i<m_NumChars; i++ )
                {
                    m_Chars[i].id = *(unsigned int*)fileptr;
                    fileptr += sizeof( m_Chars[i].id );

                    m_Chars[i].x = *(unsigned short*)fileptr;
                    fileptr += sizeof( m_Chars[i].x );

                    m_Chars[i].y = *(unsigned short*)fileptr;
                    fileptr += sizeof( m_Chars[i].y );

                    m_Chars[i].width = *(unsigned short*)fileptr;
                    fileptr += sizeof( m_Chars[i].width );

                    m_Chars[i].height = *(unsigned short*)fileptr;
                    fileptr += sizeof( m_Chars[i].height );

                    m_Chars[i].xoffset = *(short*)fileptr;
                    fileptr += sizeof( m_Chars[i].xoffset );

                    m_Chars[i].yoffset = *(short*)fileptr;
                    fileptr += sizeof( m_Chars[i].yoffset );

                    m_Chars[i].xadvance = *(short*)fileptr;
                    fileptr += sizeof( m_Chars[i].xadvance );

                    m_Chars[i].page = *(unsigned char*)fileptr;
                    fileptr += sizeof( m_Chars[i].page );

                    m_Chars[i].chnl = *(unsigned char*)fileptr;
                    fileptr += sizeof( m_Chars[i].chnl );
                }
            }
            break;

        case 5: // Block type 5: kerning pairs
            {
                fileptr += 1; // skip past the block type.
                unsigned int blocksize = *(unsigned int*)fileptr;
                fileptr += 4; // skip past size;
            
                m_NumKerningPairs = blocksize / 10;

                m_KerningPairs = new KerningPair[m_NumKerningPairs];

                for( unsigned int i=0; i<m_NumKerningPairs; i++ )
                {
                    m_KerningPairs[i].first = *(unsigned int*)fileptr;
                    fileptr += sizeof( m_KerningPairs[i].first );

                    m_KerningPairs[i].second = *(unsigned int*)fileptr;
                    fileptr += sizeof( m_KerningPairs[i].second );

                    m_KerningPairs[i].amount = *(short*)fileptr;
                    fileptr += sizeof( m_KerningPairs[i].amount );
                }
            }
            break;
        }
    }

    //ErrorLog( "Font Initialized - %s with %d chars.\n", m_ImageName, m_NumChars );
    m_Initialized = true;
}

TextureFont::FontProperties TextureFont::fontProperties()
{
	return m_Properties;
}


unsigned int TextureFont::getNumberOfCharacters()
{
	return m_NumChars;
}


TextureFont::CharDescriptor TextureFont::getCharacter(int index)
{
	return m_Chars[index];
}