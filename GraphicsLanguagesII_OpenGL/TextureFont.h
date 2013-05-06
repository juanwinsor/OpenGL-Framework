#ifndef __TEXTUREFONT_H
#define __TEXTUREFONT_H

#define Justify_Top         0x01
#define Justify_Bottom      0x02
#define Justify_CenterY     0x04
#define Justify_Left        0x08
#define Justify_Right       0x10
#define Justify_CenterX     0x20

#include <Windows.h>


class TextureFont
{
public:
	struct FontProperties
    {
        //<info face="System" size="24" bold="0" italic="0" charset="" unicode="1" stretchH="100" smooth="1" aa="1" padding="0,0,0,0" spacing="1,1" outline="0"/>
        //<common lineHeight="16" base="13" scaleW="128" scaleH="128" pages="1" packed="0" alphaChnl="0" redChnl="4" greenChnl="4" blueChnl="4"/>
        //  <page id="0" file="dontcheckin-testing_0.png" />

        unsigned short lineHeight;  // This is the distance in pixels between each line of text.
        unsigned short base;        // The number of pixels from the absolute top of the line to the base of the characters.
        unsigned short scaleW;      // The width of the texture, normally used to scale the x pos of the character image.
        unsigned short scaleH;
        unsigned short pages;       // The number of texture pages included in the font.
        bool packed;                // Set to 1 if the monochrome characters have been packed into each of the texture channels. In this case alphaChnl describes what is stored in each channel.
        unsigned char alphaChnl;    // Set to 0 if the channel holds the glyph data, 1 if it holds the outline, 2 if it holds the glyph and the outline, 3 if its set to zero, and 4 if its set to one.
        unsigned char redChnl;
        unsigned char greenChnl;
        unsigned char blueChnl;
    };

    struct CharDescriptor
    {
        //<char id="32" x="85" y="33" width="4" height="0" xoffset="0" yoffset="16" xadvance="4" page="0" chnl="15" />

        unsigned int id;
        unsigned short x;       // The left position of the character image in the texture.
        unsigned short y;
        unsigned short width;   // The width of the character image in the texture.
        unsigned short height;
        short xoffset;          // How much the current position should be offset when copying the image from the texture to the screen.
        short yoffset;
        short xadvance;         // How much the current position should be advanced after drawing the character.
        unsigned char page;     // The texture page where the character image is found.
        unsigned char chnl;     // The texture channel where the character image is found (1 = blue, 2 = green, 4 = red, 8 = alpha, 15 = all channels).
    };

    struct KerningPair
    {
        unsigned int first;     // The first character id.
        unsigned int second;    // The second character id.
        short amount;           // How much the x position should be adjusted when drawing the second character immediately following the first.
    };

protected:
	bool m_Initialized;
    char m_ImageName[MAX_PATH];
    FontProperties m_Properties;
    CharDescriptor* m_Chars;
    KerningPair* m_KerningPairs;
    unsigned int m_NumChars; // number of characters in font.
    unsigned int m_NumKerningPairs;

	GLuint m_FontTextureID;

    void ReadFont(char* filebuffer, unsigned int buffersize);
	void LoadFontImage();
public:
	TextureFont(char* filename);
	virtual ~TextureFont();
	char* QueryImageName() { return m_ImageName; }
	unsigned short QueryLineHeight() { return m_Properties.lineHeight; }

	//getters
	FontProperties fontProperties();
	unsigned int getNumberOfCharacters();
	CharDescriptor getCharacter(int index);
	GLuint getFontTexture();
};


#endif 