/**
* @file		CImageLoader.h
* @author	Jesús Alberto Del Moral Cupil
* @e	    idv18c.jmoral@uartesdigitales.edu.mx
* @date		14/10/2020
* @brief	A basic description of the what do the doc.
* @bug		No know Bugs.
**/

#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <windows.h>

/**
* @class    CImageLoader.
* @brief    Specific constructor.
* @bug      No know Bugs.
**/
class CImageLoader {
public:

    /**
    * @brief    Constructor.
    * @bug      No know Bugs.
    **/
	CImageLoader();

    /**
    * @brief    Destructor.
    * @bug      No know Bugs.
    **/
	~CImageLoader();

    /**
    * @brief    Read data from file.
    * @param    inFileName Name of the file.
    * @bug      No know Bugs.
    **/
    void loadBMP(std::string inFileName);

    /**
    * @brief    Getter for Width.
    * @bug      No know Bugs.
    * @return   Returns the width.
    **/
    unsigned int getWidth() { return m_Width; }

    /**
    * @brief    Getter for Height.
    * @bug      No know Bugs.
    * @return   Returns the height.
    **/
    unsigned int getHeight() { return m_Height; }
    
    /**
    * @brief    Getter for bytes per pixel.
    * @bug      No know Bugs.
    * @return   Returns the bytes.
    **/
    unsigned int getBPP() { return m_BPP; }

    /**
    * @brief    Getter for image.
    * @bug      No know Bugs.
    * @return   Returns the data of the image.
    **/
    const char* getImgData() { return m_Img.data(); }

   /**
   * @brief    Getter for line pitch.
   * @bug      No know Bugs.
   * @return   Returns the length in bytes of a line.
   **/
    unsigned int getPitch() { return m_Width * m_BPP; }

   /**
   * @brief    Getter for full image size.
   * @bug      No know Bugs.
   * @return   Returns the full size in bytes.
   **/
    unsigned int getImgSize() { return m_Width * m_Height * m_BPP; }

    /**
   * @brief    Clears the variables to use it again.
   * @bug      No know Bugs.
   **/
    void clearData();
private:

    
    unsigned int m_Width = 0;


    unsigned int m_Height = 0;

    ///Bytes per pixel
    unsigned int m_BPP = 0;

    ///Image Data bytes
    std::vector<char> m_Img;


};

