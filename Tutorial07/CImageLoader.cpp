#include "CImageLoader.h"

CImageLoader::CImageLoader() {
	
}


CImageLoader::~CImageLoader() {


}


void CImageLoader::loadBMP(std::string inFileName) {

	//Clear the variables to use it
	clearData();

	std::ifstream FS;
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;

	//Open File
	FS.open(inFileName, std::ios::binary);

	//Save header from file
	FS.read((char*)&fileHeader, sizeof(fileHeader));
	FS.read((char*)&infoHeader, sizeof(infoHeader));

	//Save height and width
	m_Width = infoHeader.biWidth;
	m_Height = infoHeader.biHeight;
	m_BPP = infoHeader.biBitCount / 8;

	//Resize to data vector
	m_Img.resize(infoHeader.biSizeImage);

	//Read image from file
	FS.read(m_Img.data(), m_Img.size());

	char temp = 0;
	for (int i = infoHeader.biSizeImage - 1 - m_BPP; i >= 0; i -= m_BPP) {
		//0xbbggrraa
		//0xaarrggbb
		temp = m_Img[i + 1];
		m_Img[i + 1] = m_Img[i + 3];
		m_Img[i + 3] = temp;


		/*std::cout << "R: " << int(m_Img[i] & 0xff) << 
					 " G: " << int(m_Img[i + 1] & 0xff) << 
					 " B: " << int(m_Img[i + 2] & 0xff) << std::endl;*/
	}

	//Close File
	FS.close();
}


void CImageLoader::clearData() {
	m_Width = 0;
	m_Height = 0;
	m_BPP = 0;
	m_Img.clear();
}
