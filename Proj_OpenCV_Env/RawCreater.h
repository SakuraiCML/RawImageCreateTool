#pragma once

#pragma warning(disable : 26439)

// OpenCV include
#include "opencv2/opencv.hpp"
#include <fstream>

enum class colorPattern {
    RGGB,
    GRBG,
    GBRG,
    BGGR,
};

enum class format {
    RAW8,
    RAW10,
    RAW12,
    RAW16,
};

class RawCreater {
    //* Consructor
public:
    RawCreater();
    ~RawCreater();

    RawCreater(int argc, char* argv[]);

    //* Parameter
public:
    int m_argc = 0;
    char** m_argv = nullptr;
    //** parameter initial **
    int m_nImgW = 0;
    int m_nImgH = 0;
    colorPattern m_cp = colorPattern::RGGB;
    format m_ft = format::RAW8;
    int m_R = 0;
    int m_G = 0;
    int m_B = 0;
    cv::Mat mImg;
    cv::Mat mImgSFR;
    int m_nCV_type = 0;
    unsigned char* SaveRawBuffer = nullptr;

    //* function
public:
    //* parameter judge and input to member
    int Initial();
    //* show result image
    bool ShowImg(int waitKeyTime = 0);
    //* show image temp
    void ShowImg(std::string strTitle, cv::Mat img, int waitKeyTime = 0);
    //* create bayer image
    int CreateRawImg();
    //* save image
    bool SaveImg(std::string strName = "Result");

    //* SFR chess chart
    void SFRChessChart(int block_width, int block_height, double rotate_degree);

    //* sub function
public:
    std::string RawFormat_Str(format m_ft);
    std::string ColorPattern_Str(colorPattern m_cp);
private:
    void normalizedColor(double* Color_vector, int nColor, int nRange, int nDL);
    void Image_Full(cv::Mat& _Img);
    void CreateRaw(cv::Mat& _srcImg, unsigned char* _Buffer);
    void SaveRaw(std::string str_name, unsigned char* _Buffer);
    //* rotate function
    cv::Point rotateD(cv::Point inPoint, cv::Point centerPoint, double Dgree);

};

