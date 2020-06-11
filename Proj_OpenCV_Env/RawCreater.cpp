#include "RawCreater.h"

RawCreater::RawCreater() {
}

RawCreater::~RawCreater() {
}

RawCreater::RawCreater(int argc, char* argv[]) {
    //** argv list **
    //* argv[0] : .exe name
    //* argv[1] : Image Width
    //* argv[2] : Image Height
    //* argv[3] : Image Color Patern
    //* argv[4] : Image raw format
    //* argv[5] : R
    //* argv[6] : G
    //* argv[7] : B
    m_argc = argc;
    m_argv = argv;
}

int RawCreater::Initial() {
    //** check argc length
    if (m_argc <= 1) {
        std::cout << "Not enough parameter input" << std::endl;
        std::cout << "argc : " << m_argc << std::endl;
        return -1;
    }
    else {
        //* Image H,W set
        m_nImgW = std::stoi(m_argv[1]);
        m_nImgH = std::stoi(m_argv[2]);

        //* color channel set
        int cp_value = std::stoi(m_argv[3]);
        if (cp_value == 0) {
            m_cp = colorPattern::RGGB;
        }
        else if (cp_value == 1) {
            m_cp = colorPattern::GRBG;
        }
        else if (cp_value == 2) {
            m_cp = colorPattern::GBRG;
        }
        else if (cp_value == 3) {
            m_cp = colorPattern::BGGR;
        }

        //* format set
        int ft_value = std::stoi(m_argv[4]);
        if (ft_value == 0) {
            m_ft = format::RAW8;
        }
        else if (ft_value == 1) {
            m_ft = format::RAW10;
        }
        else if (ft_value == 2) {
            m_ft = format::RAW12;
        }
        else if (ft_value == 3) {
            m_ft = format::RAW16;
        }

        //* color set
        m_R = std::stoi(m_argv[5]);
        m_G = std::stoi(m_argv[6]);
        m_B = std::stoi(m_argv[7]);
        if (m_ft == format::RAW8 && (m_R > 255 || m_G > 255 || m_B > 255)) {
            std::cout << "RAW8 RGB setting range must in [0~255]" << std::endl;
            std::cout << "R : " << m_R << std::endl;
            std::cout << "G : " << m_G << std::endl;
            std::cout << "B : " << m_B << std::endl;
            return -2;
        }
        else if (m_ft == format::RAW10 && (m_R > 1023 || m_G > 1023 || m_B > 1023)) {
            std::cout << "RAW10 RGB setting range must in [0~1023]" << std::endl;
            std::cout << "R : " << m_R << std::endl;
            std::cout << "G : " << m_G << std::endl;
            std::cout << "B : " << m_B << std::endl;
            return -2;
        }
        else if (m_ft == format::RAW12 && (m_R > 4095 || m_G > 4095 || m_B > 4095)) {
            std::cout << "RAW12 RGB setting range must in [0~4095]" << std::endl;
            std::cout << "R : " << m_R << std::endl;
            std::cout << "G : " << m_G << std::endl;
            std::cout << "B : " << m_B << std::endl;
            return -2;
        }
        else if (m_ft == format::RAW16 && (m_R > 65535 || m_G > 65535 || m_B > 65535)) {
            std::cout << "RAW16 RGB setting range must in [0~65535]" << std::endl;
            std::cout << "R : " << m_R << std::endl;
            std::cout << "G : " << m_G << std::endl;
            std::cout << "B : " << m_B << std::endl;
            return -2;
        }

        //* check SFR setting param
        if (m_argc >= 11) {
            m_sfrW = std::stoi(m_argv[8]);
            m_sfrH = std::stoi(m_argv[9]);
            m_sfrDegree = std::stod(m_argv[10]);
        }
        else {
            m_sfrW = m_nImgW / 20;
            m_sfrH = m_nImgH / 20;
            m_sfrDegree = 8.0;
        }
    }

    //** set image **
    if (m_ft == format::RAW8) {
        m_nCV_type = CV_8UC1;
    }
    else {
        m_nCV_type = CV_16UC1;
    }
    cv::Mat image(m_nImgH, m_nImgW, m_nCV_type);
    image.setTo(0);

    mImg = image.clone();

    return 0;
}

bool RawCreater::ShowImg(int waitKeyTime) {

    //* avoid empty image
    if (mImg.empty()) {
        std::cout << "Image showing error" << std::endl;
        std::cout << "** Image Width : " << m_nImgW << std::endl;
        std::cout << "** Image Height : " << m_nImgH << std::endl;
        std::cout << "** Image Format : " << RawFormat_Str(m_ft) << std::endl;
        std::cout << "** Image Color Pattern : " << ColorPattern_Str(m_cp) << std::endl;
        return false;
    }

    //* window name
    int nSx = 50;
    int nSy = 10;
    int nGap = 10;
    cv::namedWindow("Raw Final");
    cv::moveWindow("Raw Final", nSx, nSy);
    cv::namedWindow("SFR Chess Chart Final");
    cv::moveWindow("SFR Chess Chart Final", nSx + mImg.cols + nGap, nSy);
    cv::namedWindow("SFR Block Chart Final");
    cv::moveWindow("SFR Block Chart Final", nSx + (mImg.cols + nGap) * 2, nSy);
    cv::namedWindow("SFR Cross Chart Final");
    cv::moveWindow("SFR Cross Chart Final", nSx, nSy + mImg.rows + nGap);
    cv::namedWindow("SFR Cross Chart Inv Final");
    cv::moveWindow("SFR Cross Chart Inv Final", nSx + mImg.cols + nGap, nSy + mImg.rows + nGap);

    //* window parameter
    if (m_ft == format::RAW8 || m_ft == format::RAW16) {
        cv::imshow("SFR Chess Chart Final", mImgSFR); cv::waitKey(1);
        cv::imshow("SFR Block Chart Final", mImgSFR_Block); cv::waitKey(1);
        cv::imshow("SFR Cross Chart Final", mImgSFR_Cross); cv::waitKey(1);
        cv::imshow("SFR Cross Chart Inv Final", mImgSFR_Cross_Inv); cv::waitKey(1);
        cv::imshow("Raw Final", mImg); cv::waitKey(waitKeyTime);
    }
    else if (m_ft == format::RAW10) {
        //* move color range Raw10 To Raw16 
        cv::imshow("SFR Chess Chart Final", mImgSFR * 64); cv::waitKey(1);
        cv::imshow("SFR Block Chart Final", mImgSFR_Block * 64); cv::waitKey(1);
        cv::imshow("SFR Cross Chart Final", mImgSFR_Cross * 64); cv::waitKey(1);
        cv::imshow("SFR Cross Chart Inv Final", mImgSFR_Cross_Inv * 64); cv::waitKey(1);
        cv::imshow("Raw Final", mImg * 64); cv::waitKey(waitKeyTime);
    }
    else if (m_ft == format::RAW12) {
        //* move color range Raw12 To Raw16 
        cv::imshow("SFR Chess Chart Final", mImgSFR * 16); cv::waitKey(1);
        cv::imshow("SFR Block Chart Final", mImgSFR_Block * 16); cv::waitKey(1);
        cv::imshow("SFR Cross Chart Final", mImgSFR_Cross * 16); cv::waitKey(1);
        cv::imshow("SFR Cross Chart Inv Final", mImgSFR_Cross_Inv * 16); cv::waitKey(1);
        cv::imshow("Raw Final", mImg * 16); cv::waitKey(waitKeyTime);
    }
    return true;
}

void RawCreater::ShowImg(std::string strTitle, cv::Mat img, int waitKeyTime) {
    cv::destroyWindow(strTitle);
    //* window parameter
    if (m_ft == format::RAW8 || m_ft == format::RAW16) {
        cv::imshow(strTitle, img); cv::waitKey(waitKeyTime);
    }
    else if (m_ft == format::RAW10) {
        //* move color range Raw10 To Raw16 
        cv::imshow(strTitle, img * 64); cv::waitKey(waitKeyTime);
    }
    else if (m_ft == format::RAW12) {
        //* move color range Raw12 To Raw16 
        cv::imshow(strTitle, img * 16); cv::waitKey(waitKeyTime);
    }
}

int RawCreater::CreateRawImg() {
    //* Test
    cv::Mat imgR(m_nImgH, m_nImgW, m_nCV_type + 8 * 2);
    imgR = cv::Scalar(0, 0, m_R);
    cv::Mat imgG(m_nImgH, m_nImgW, m_nCV_type + 8 * 2);
    imgG = cv::Scalar(0, m_G, 0);
    cv::Mat imgB(m_nImgH, m_nImgW, m_nCV_type + 8 * 2);
    imgB = cv::Scalar(m_B, 0, 0);
    cv::Mat matBMP(m_nImgH, m_nImgW, m_nCV_type + 8 * 2);
    matBMP = cv::Scalar(m_B, m_G, m_R);

    //* show image
    //ShowImg("TR", imgR, 1);
    //ShowImg("TG", imgG, 1);
    //ShowImg("TB", imgB, 1);
    //ShowImg("TT", matBMP, 1);    

    //** Gaussian Distribution **
    //* diagonal
    int nMax_W = (int)sqrt(m_nImgW * m_nImgW + m_nImgH * m_nImgH);
    int nU = nMax_W / 2;
    int nLength = nMax_W;
    double sum_x_square = 0.0;
    for (int i = 0; i < nLength; i++) {
        sum_x_square += i * i;
    }
    int nSD = (int)sqrt(sum_x_square / (double)nLength - double(nU * nU));
    //* gaussian coefficient
    double* dGaussCoeff = new double[nMax_W];
    //* R channel
    double* R_index = new double[nMax_W];
    double* G_index = new double[nMax_W];
    double* B_index = new double[nMax_W];
    for (int i = 0; i < nMax_W; i++) {
        dGaussCoeff[i] = (1 / (nSD * sqrt(2 * 3.141592))) * exp(-((i - nU) * (i - nU)) / (2 * nSD * nSD));
        R_index[i] = m_R * dGaussCoeff[i];
        G_index[i] = m_G * dGaussCoeff[i];
        B_index[i] = m_B * dGaussCoeff[i];
    }

    //* Normalized
    int nRange = 2;
    normalizedColor(R_index, m_R, nRange, nMax_W);
    normalizedColor(G_index, m_G, nRange, nMax_W);
    normalizedColor(B_index, m_B, nRange, nMax_W);

    //* input data
    imgR.setTo(0);
    imgG.setTo(0);
    imgB.setTo(0);
    matBMP.setTo(0);
    for (int x = 0; x < m_nImgW / 2; x++) {
        for (int y = 0; y < m_nImgH / 2; y++) {
            int nIdx = (int)sqrt((x - m_nImgW / 2) * (x - m_nImgW / 2) + (y - m_nImgH / 2) * (y - m_nImgH / 2));
            if (nIdx < nMax_W) {
                if (m_nCV_type == CV_16UC1) {
                    imgR.at<cv::Vec3w>(y, x)[2] = (unsigned int)R_index[nU - nIdx];
                    imgG.at<cv::Vec3w>(y, x)[1] = (unsigned int)G_index[nU - nIdx];
                    imgB.at<cv::Vec3w>(y, x)[0] = (unsigned int)B_index[nU - nIdx];

                    matBMP.at<cv::Vec3w>(y, x)[2] = (unsigned int)R_index[nU - nIdx];
                    matBMP.at<cv::Vec3w>(y, x)[1] = (unsigned int)G_index[nU - nIdx];
                    matBMP.at<cv::Vec3w>(y, x)[0] = (unsigned int)B_index[nU - nIdx];
                }
                else if (m_nCV_type == CV_8UC1) {
                    imgR.at<cv::Vec3b>(y, x)[2] = (unsigned char)R_index[nU - nIdx];
                    imgG.at<cv::Vec3b>(y, x)[1] = (unsigned char)G_index[nU - nIdx];
                    imgB.at<cv::Vec3b>(y, x)[0] = (unsigned char)B_index[nU - nIdx];

                    matBMP.at<cv::Vec3b>(y, x)[2] = (unsigned char)R_index[nU - nIdx];
                    matBMP.at<cv::Vec3b>(y, x)[1] = (unsigned char)G_index[nU - nIdx];
                    matBMP.at<cv::Vec3b>(y, x)[0] = (unsigned char)B_index[nU - nIdx];
                }
            }
        }
    }

    //* flip and full the Image
    Image_Full(imgR);
    Image_Full(imgG);
    Image_Full(imgB);
    Image_Full(matBMP);

    //* result
    //ShowImg("TR_G", imgR, 1);
    //ShowImg("TG_G", imgG, 1);
    //ShowImg("TB_G", imgB, 1);
    //ShowImg("TT_G", matBMP, 1);

    //* smooth - gauss blur
    int nS = 15;
    if (nS % 2 == 0) {
        nS -= 1;
    }
    for (size_t i = 0; i < 1; i++) {
        cv::GaussianBlur(matBMP, matBMP, cv::Size(nS, nS), nS / 2);
    }
    mImg = matBMP.clone();
    //ShowImg("TT_G_S", matBMP, 0);

    delete[] dGaussCoeff; dGaussCoeff = nullptr;
    delete[] R_index; R_index = nullptr;
    delete[] G_index; G_index = nullptr;
    delete[] B_index; B_index = nullptr;

    return 0;
}

bool RawCreater::SaveImg(std::string strName) {
    //* Save string
    std::string  strSavePath = "SaveImg/" + strName;

    //* write bmp
    if (m_ft == format::RAW8) {
        //* bmp
        cv::imwrite(strSavePath + ".bmp", mImg);
        cv::imwrite(strSavePath + "sfrChess.bmp", mImgSFR);
        cv::imwrite(strSavePath + "sfrCross.bmp", mImgSFR_Cross);
        cv::imwrite(strSavePath + "sfrCrossInv.bmp", mImgSFR_Cross_Inv);
        cv::imwrite(strSavePath + "sfrBlock.bmp", mImgSFR_Block);

        //* raw
        unsigned char* Buffer = new unsigned char[m_nImgH * m_nImgW];
        CreateRaw(mImg, Buffer);
        SaveRaw(strSavePath, Buffer);
        CreateRaw(mImgSFR, Buffer);
        SaveRaw(strSavePath + "sfrChess", Buffer);
        CreateRaw(mImgSFR_Cross, Buffer);
        SaveRaw(strSavePath + "sfrCross", Buffer);
        CreateRaw(mImgSFR_Cross_Inv, Buffer);
        SaveRaw(strSavePath + "sfrCrossInv", Buffer);
        CreateRaw(mImgSFR_Block, Buffer);
        SaveRaw(strSavePath + "sfrBlock", Buffer);
        delete[] Buffer; Buffer = nullptr;
    }
    else if (m_ft == format::RAW10) {
        //* 1024 -> 256

        //* bmp
        cv::imwrite(strSavePath + ".bmp", mImg / 4);
        cv::imwrite(strSavePath + "sfrChess.bmp", mImgSFR / 4);
        cv::imwrite(strSavePath + "sfrCross.bmp", mImgSFR_Cross / 4);
        cv::imwrite(strSavePath + "sfrCrossInv.bmp", mImgSFR_Cross_Inv / 4);
        cv::imwrite(strSavePath + "sfrBlock.bmp", mImgSFR_Block / 4);

        //* raw
        unsigned char* Buffer = new unsigned char[m_nImgH * m_nImgW * 2];
        CreateRaw(mImg, Buffer);
        SaveRaw(strSavePath, Buffer);
        CreateRaw(mImgSFR, Buffer);
        SaveRaw(strSavePath + "sfrChess", Buffer);
        CreateRaw(mImgSFR_Cross, Buffer);
        SaveRaw(strSavePath + "sfrCross", Buffer);
        CreateRaw(mImgSFR_Cross_Inv, Buffer);
        SaveRaw(strSavePath + "sfrCrossInv", Buffer);
        CreateRaw(mImgSFR_Block, Buffer);
        SaveRaw(strSavePath + "sfrBlock", Buffer);
        delete[] Buffer; Buffer = nullptr;
    }
    else if (m_ft == format::RAW12) {
        //* 4096 -> 256

        //* bmp
        cv::imwrite(strSavePath + ".bmp", mImg / 16);
        cv::imwrite(strSavePath + "sfrChess.bmp", mImgSFR / 16);
        cv::imwrite(strSavePath + "sfrCross.bmp", mImgSFR_Cross / 16);
        cv::imwrite(strSavePath + "sfrCrossInv.bmp", mImgSFR_Cross_Inv / 16);
        cv::imwrite(strSavePath + "sfrBlock.bmp", mImgSFR_Block / 16);

        //* raw
        unsigned char* Buffer = new unsigned char[m_nImgH * m_nImgW * 2];
        CreateRaw(mImg, Buffer);
        SaveRaw(strSavePath, Buffer);
        CreateRaw(mImgSFR, Buffer);
        SaveRaw(strSavePath + "sfrChess", Buffer);
        CreateRaw(mImgSFR_Cross, Buffer);
        SaveRaw(strSavePath + "sfrCross", Buffer);
        CreateRaw(mImgSFR_Cross_Inv, Buffer);
        SaveRaw(strSavePath + "sfrCrossInv", Buffer);
        CreateRaw(mImgSFR_Block, Buffer);
        SaveRaw(strSavePath + "sfrBlock", Buffer);
        delete[] Buffer; Buffer = nullptr;
    }
    else if (m_ft == format::RAW16) {
        //* 65536 -> 256

        //* bmp
        cv::imwrite(strSavePath + ".bmp", mImg / 256);
        cv::imwrite(strSavePath + "sfrChess.bmp", mImgSFR / 256);
        cv::imwrite(strSavePath + "sfrCross.bmp", mImgSFR_Cross / 256);
        cv::imwrite(strSavePath + "sfrCrossInv.bmp", mImgSFR_Cross_Inv / 256);
        cv::imwrite(strSavePath + "sfrBlock.bmp", mImgSFR_Block / 256);

        //* raw
        unsigned char* Buffer = new unsigned char[m_nImgH * m_nImgW * 2];
        CreateRaw(mImg, Buffer);
        SaveRaw(strSavePath, Buffer);
        CreateRaw(mImgSFR, Buffer);
        SaveRaw(strSavePath + "sfrChess", Buffer);
        CreateRaw(mImgSFR_Cross, Buffer);
        SaveRaw(strSavePath + "sfrCross", Buffer);
        CreateRaw(mImgSFR_Cross_Inv, Buffer);
        SaveRaw(strSavePath + "sfrCrossInv", Buffer);
        CreateRaw(mImgSFR_Block, Buffer);
        SaveRaw(strSavePath + "sfrBlock", Buffer);
        delete[] Buffer; Buffer = nullptr;
    }

    return true;
}

void RawCreater::SFRChessChart(int block_width, int block_height, double rotate_degree) {
    cv::Mat temp(mImg.rows * 2, mImg.cols * 2, mImg.type());
    mImg.copyTo(temp(cv::Rect(0, 0, m_nImgW, m_nImgH)));
    //ShowImg("TT_G_SV", temp, 0);
    mImg.copyTo(temp(cv::Rect(m_nImgW, 0, m_nImgW, m_nImgH)));
    //ShowImg("TT_G_SV", temp, 0);
    mImg.copyTo(temp(cv::Rect(0, m_nImgH, m_nImgW, m_nImgH)));
    //ShowImg("TT_G_SV", temp, 0);
    mImg.copyTo(temp(cv::Rect(m_nImgW, m_nImgH, m_nImgW, m_nImgH)));
    //ShowImg("TT_G_SV", temp, 0);
    //cv::Mat mtBlock(block_height, block_width, temp.type());
    //mtBlock.setTo(0);

    //* Image Center
    int nCC_x = m_nImgW;
    int nCC_y = m_nImgH;

    int m_nSplit_Y = m_nImgH * 2 / block_height;
    int m_nSplit_X = m_nImgW * 2 / block_width;

    //* moving index
    int nMoveX = m_nSplit_X / 2;
    int nMoveY = m_nSplit_Y / 2;;

    for (int y = 0; y < m_nSplit_Y; y += 2) {
        for (int x = 0; x < m_nSplit_X; x += 2) {
            int nL = nCC_x - (nMoveX - x) * block_width - block_width / 2;
            int nT = nCC_y - (nMoveY - y) * block_height - block_height / 2;
            cv::Rect rt = cv::Rect(nL, nT, block_width, block_height);
            if (rt.x < 0 || rt.y < 0 || rt.y + rt.height > m_nImgH * 2 || rt.x + rt.width > m_nImgW * 2) {
                if (rt.y < 0) {
                    rt.height += rt.y;
                    rt.y = 0;
                }
                if (rt.x < 0) {
                    rt.width += rt.x;
                    rt.x = 0;
                }
                if (rt.y + rt.height > m_nImgH * 2) {
                    rt.height -= (rt.y + rt.height - m_nImgH * 2);
                }
                if (rt.x + rt.width > m_nImgW * 2) {
                    rt.width -= (rt.x + rt.width - m_nImgW * 2);
                }
            }
            temp(rt).setTo(0);
            //ShowImg("TT_G_SV", temp, 0);
            nL = nCC_x - (nMoveX - x - 1) * block_width - block_width / 2;
            nT = nCC_y - (nMoveY - y - 1) * block_height - block_height / 2;
            rt = cv::Rect(nL, nT, block_width, block_height);
            if (rt.x < 0 || rt.y < 0 || rt.y + rt.height > m_nImgH * 2 || rt.x + rt.width > m_nImgW * 2) {
                if (rt.y < 0) {
                    rt.height += rt.y;
                    rt.y = 0;
                }
                if (rt.x < 0) {
                    rt.width += rt.x;
                    rt.x = 0;
                }
                if (rt.y + rt.height > m_nImgH * 2) {
                    rt.height -= (rt.y + rt.height - m_nImgH * 2);
                }
                if (rt.x + rt.width > m_nImgW * 2) {
                    rt.width -= (rt.x + rt.width - m_nImgW * 2);
                }
            }
            temp(rt).setTo(0);
            //ShowImg("TT_G_SV", temp, 0);
        }
    }
    //ShowImg("TT_TEMP", temp, 0);

    cv::Mat temp2 = temp.clone();
    temp2.setTo(0);
    for (size_t row = 0; row < (size_t)temp.rows; row++) {
        for (size_t col = 0; col < (size_t)temp.cols; col++) {
            cv::Point in((int)col, (int)row);
            cv::Point out = rotateD(in, cv::Point(temp.cols / 2, temp.rows / 2), rotate_degree);
            if (out.x > 0 && out.x < m_nImgW * 2 && out.y>0 && out.y < m_nImgH * 2) {
                temp(cv::Rect(out.x, out.y, 1, 1)).copyTo(temp2(cv::Rect(in.x, in.y, 1, 1)));
            }
        }
    }
    //ShowImg("TT_TEMP2", temp2, 0);

    mImgSFR = temp2(cv::Rect(m_nImgW - m_nImgW / 2, m_nImgH - m_nImgH / 2, m_nImgW, m_nImgH)).clone();
    cv::GaussianBlur(mImgSFR, mImgSFR, cv::Size(3, 3), 0);
    //ShowImg("TT_G_SR", mImgSFR, 0);
}

void RawCreater::SFRCrossChart(int block_width, int block_height, double rotate_degree) {
    //* mask
    cv::Mat mask(m_sfrH, m_sfrW, CV_8UC1); mask.setTo(0);
    int rad = (m_sfrH < m_sfrW) ? m_sfrH / 2 : m_sfrW / 2;
    cv::circle(mask, cv::Point(mask.cols / 2, mask.rows / 2), rad, cv::Scalar(255), -1);
    //ShowImg("TT_M", mask, 1);

    //* chart template
    cv::Mat temp = mImg(cv::Rect(mImg.cols / 2 - m_sfrW, mImg.rows / 2 - m_sfrH, 2 * m_sfrW, 2 * m_sfrH)).clone();
    temp(cv::Rect(0, 0, m_sfrW, m_sfrH)).setTo(0);
    temp(cv::Rect(m_sfrW, m_sfrH, m_sfrW, m_sfrH)).setTo(0);
    //ShowImg("TT_Chart", temp, 1);

    cv::Mat chartTemp = temp.clone();
    chartTemp.setTo(0);
    for (size_t row = 0; row < (size_t)temp.rows; row++) {
        for (size_t col = 0; col < (size_t)temp.cols; col++) {
            cv::Point in((int)col, (int)row);
            cv::Point out = rotateD(in, cv::Point(temp.cols / 2, temp.rows / 2), rotate_degree);
            if (out.x > 0 && out.x < temp.cols && out.y>0 && out.y < temp.rows) {
                //temp(cv::Rect(in.x, in.y, 1, 1)).copyTo(temp2(cv::Rect(out.x, out.y, 1, 1)));
                temp(cv::Rect(out.x, out.y, 1, 1)).copyTo(chartTemp(cv::Rect(in.x, in.y, 1, 1)));
            }
        }
    }
    //cv::GaussianBlur(chartTemp, chartTemp, cv::Size(3, 3), 0);
    //ShowImg("TT_ChartR", chartTemp, 0);
    chartTemp = chartTemp(cv::Rect(temp.cols / 2 - m_sfrW / 2, temp.rows / 2 - m_sfrH / 2, m_sfrW, m_sfrH)).clone();
    //ShowImg("TT_ChartR", chartTemp, 1);

    //* create
    mImgSFR_Cross = mImg.clone();
    mImgSFR_Cross_Inv = mImg.clone(); mImgSFR_Cross_Inv.setTo(0);
    int nCx = mImgSFR_Cross.cols / 2;
    int nCy = mImgSFR_Cross.rows / 2;

    std::vector<cv::Rect> sfrLocs;
    //center
    sfrLocs.push_back(cv::Rect(nCx - m_sfrW / 2, nCy - m_sfrH / 2, m_sfrW, m_sfrH));
    //0.4F & 0.8F
    for (int i = 5; i <= 8; i += 3) {
        double dfield = i * 0.1;
        //LT & RT & LB & RB
        sfrLocs.push_back(cv::Rect(int(nCx - dfield * nCx) - m_sfrW / 2, int(nCy - dfield * nCy) - m_sfrH / 2, m_sfrW, m_sfrH));
        sfrLocs.push_back(cv::Rect(int(nCx + dfield * nCx) - m_sfrW / 2, int(nCy - dfield * nCy) - m_sfrH / 2, m_sfrW, m_sfrH));
        sfrLocs.push_back(cv::Rect(int(nCx - dfield * nCx) - m_sfrW / 2, int(nCy + dfield * nCy) - m_sfrH / 2, m_sfrW, m_sfrH));
        sfrLocs.push_back(cv::Rect(int(nCx + dfield * nCx) - m_sfrW / 2, int(nCy + dfield * nCy) - m_sfrH / 2, m_sfrW, m_sfrH));
        if (i == 5) {
            double dLenth = sqrt(nCx * nCx + nCy * nCy) * dfield;
            //T & B & L & R
            sfrLocs.push_back(cv::Rect(nCx - m_sfrW / 2, int(nCy - dLenth) - m_sfrH / 2, m_sfrW, m_sfrH));
            sfrLocs.push_back(cv::Rect(nCx - m_sfrW / 2, int(nCy + dLenth) - m_sfrH / 2, m_sfrW, m_sfrH));
            sfrLocs.push_back(cv::Rect(int(nCx - dLenth) - m_sfrW / 2, nCy - m_sfrH / 2, m_sfrW, m_sfrH));
            sfrLocs.push_back(cv::Rect(int(nCx + dLenth) - m_sfrW / 2, nCy - m_sfrH / 2, m_sfrW, m_sfrH));
        }
    }
    //put
    for (auto& loc : sfrLocs) {
        //* location & chart size is all out of draw area
        if (loc.x + loc.width < 0 || loc.x > mImgSFR_Cross.cols || loc.y + loc.height < 0 || loc.y > mImgSFR_Cross.rows) {
            continue;
        }

        //*still can draw
        if (loc.x < 0 || loc.y < 0 || loc.x + loc.width > mImgSFR_Cross.cols || loc.y + loc.height > mImgSFR_Cross.rows) {
            cv::Rect rt(0, 0, m_sfrW, m_sfrH);
            if (loc.x < 0) {
                rt.x = -loc.x;
                rt.width += loc.x;
                loc.width += loc.x;
                loc.x = 0;
            }
            if (loc.y < 0) {
                rt.y = -loc.y;
                rt.height += loc.y;
                loc.height += loc.y;
                loc.y = 0;
            }
            if (loc.x + loc.width > mImgSFR_Cross.cols) {
                int diff = loc.x + loc.width - mImgSFR_Cross.cols + 1;
                rt.width -= diff;
                loc.width -= diff;
            }
            if (loc.y + loc.height > mImgSFR_Cross.rows) {
                int diff = loc.y + loc.height - mImgSFR_Cross.rows + 1;
                rt.height -= diff;
                loc.height -= diff;
            }
            chartTemp(rt).copyTo(mImgSFR_Cross(loc), mask(rt));
            chartTemp(rt).copyTo(mImgSFR_Cross_Inv(loc), mask(rt));
        }
        else {
            chartTemp.copyTo(mImgSFR_Cross(loc), mask);
            chartTemp.copyTo(mImgSFR_Cross_Inv(loc), mask);
        }
    }

    cv::GaussianBlur(mImgSFR_Cross, mImgSFR_Cross, cv::Size(3, 3), 0);
    cv::GaussianBlur(mImgSFR_Cross_Inv, mImgSFR_Cross_Inv, cv::Size(3, 3), 0);
    //ShowImg("TT_ChartRes", mImgSFR_Cross, 1);
    //ShowImg("TT_ChartRes_Inv", mImgSFR_Cross_Inv, 1);
}

void RawCreater::SFRBlockChart(int block_width, int block_height, double rotate_degree) {
    //* chart template
    cv::Mat temp = mImg(cv::Rect(mImg.cols / 2 - m_sfrW, mImg.rows / 2 - m_sfrH, 2 * m_sfrW, 2 * m_sfrH)).clone();
    temp(cv::Rect(temp.cols / 2 - m_sfrW / 2, temp.rows / 2 - m_sfrH / 2, m_sfrW, m_sfrH)).setTo(0);
    //ShowImg("TT_Chart", temp, 0);

    //* rotate
    cv::Mat chartTemp = temp.clone(); chartTemp.setTo(0);
    for (size_t row = 0; row < (size_t)temp.rows; row++) {
        for (size_t col = 0; col < (size_t)temp.cols; col++) {
            cv::Point in((int)col, (int)row);
            cv::Point out = rotateD(in, cv::Point(temp.cols / 2, temp.rows / 2), rotate_degree);
            if (out.x > 0 && out.x < temp.cols && out.y>0 && out.y < temp.rows) {
                temp(cv::Rect(out.x, out.y, 1, 1)).copyTo(chartTemp(cv::Rect(in.x, in.y, 1, 1)));
            }
        }
    }
    //ShowImg("TT_ChartR", chartTemp, 0);

    //* crop useful image
    double dd = (rotate_degree > 0) ? rotate_degree : 90 + rotate_degree;
    double cosd = cos(dd * 3.141592 / 180.0);
    double sind = sin(dd * 3.141592 / 180.0);
    int nLengthW = int(m_sfrW * cosd + m_sfrW * sind) + 10;
    int nLengthH = int(m_sfrH * cosd + m_sfrH * sind) + 10;
    chartTemp = chartTemp(cv::Rect(chartTemp.cols / 2 - nLengthW / 2, chartTemp.rows / 2 - nLengthH / 2, nLengthW, nLengthH)).clone();
    //ShowImg("TT_ChartR", chartTemp, 0);

    cv::Mat mask = chartTemp.clone();
    mask.convertTo(mask, CV_8UC1);
    //ShowImg("TT_M", mask, 0);
    cv::threshold(mask, mask, 100, 255, cv::THRESH_BINARY_INV);
    int rad = (m_sfrH < m_sfrW) ? m_sfrH / 10 : m_sfrW / 10;
    cv::circle(mask, cv::Point(mask.cols / 2, mask.rows / 2), rad, cv::Scalar(0), -1);
    //ShowImg("TT_M", mask, 0);

    //* create
    mImgSFR_Block = mImg.clone();
    int nCx = mImgSFR_Block.cols / 2;
    int nCy = mImgSFR_Block.rows / 2;
    int nW = chartTemp.cols;
    int nH = chartTemp.rows;

    std::vector<cv::Rect> sfrLocs;
    //center
    sfrLocs.push_back(cv::Rect(nCx - nW / 2, nCy - nH / 2, nW, nH));
    //0.4F & 0.8F
    for (int i = 5; i <= 8; i += 3) {
        double dfield = i * 0.1;
        //LT & RT & LB & RB
        sfrLocs.push_back(cv::Rect(int(nCx - dfield * nCx) - nW / 2, int(nCy - dfield * nCy) - nH / 2, nW, nH));
        sfrLocs.push_back(cv::Rect(int(nCx + dfield * nCx) - nW / 2, int(nCy - dfield * nCy) - nH / 2, nW, nH));
        sfrLocs.push_back(cv::Rect(int(nCx - dfield * nCx) - nW / 2, int(nCy + dfield * nCy) - nH / 2, nW, nH));
        sfrLocs.push_back(cv::Rect(int(nCx + dfield * nCx) - nW / 2, int(nCy + dfield * nCy) - nH / 2, nW, nH));
        if (i == 5) {
            double dLenth = sqrt(nCx * nCx + nCy * nCy) * dfield;
            //T & B & L & R
            sfrLocs.push_back(cv::Rect(nCx - nW / 2, int(nCy - dLenth) - nH / 2, nW, nH));
            sfrLocs.push_back(cv::Rect(nCx - nW / 2, int(nCy + dLenth) - nH / 2, nW, nH));
            sfrLocs.push_back(cv::Rect(int(nCx - dLenth) - nW / 2, nCy - nH / 2, nW, nH));
            sfrLocs.push_back(cv::Rect(int(nCx + dLenth) - nW / 2, nCy - nH / 2, nW, nH));
        }
    }
    //put
    for (auto& loc : sfrLocs) {
        //* location & chart size is all out of draw area
        if (loc.x + loc.width < 0 || loc.x > mImgSFR_Block.cols || loc.y + loc.height < 0 || loc.y > mImgSFR_Block.rows) {
            continue;
        }

        //*still can draw
        if (loc.x < 0 || loc.y < 0 || loc.x + loc.width > mImgSFR_Block.cols || loc.y + loc.height > mImgSFR_Block.rows) {
            cv::Rect rt(0, 0, nW, nH);
            if (loc.x < 0) {
                rt.x = -loc.x;
                rt.width += loc.x;
                loc.width += loc.x;
                loc.x = 0;
            }
            if (loc.y < 0) {
                rt.y = -loc.y;
                rt.height += loc.y;
                loc.height += loc.y;
                loc.y = 0;
            }
            if (loc.x + loc.width > mImgSFR_Block.cols) {
                int diff = loc.x + loc.width - mImgSFR_Block.cols + 1;
                rt.width -= diff;
                loc.width -= diff;
            }
            if (loc.y + loc.height > mImgSFR_Block.rows) {
                int diff = loc.y + loc.height - mImgSFR_Block.rows + 1;
                rt.height -= diff;
                loc.height -= diff;
            }
            chartTemp(rt).copyTo(mImgSFR_Block(loc), mask(rt));
        }
        else {
            chartTemp.copyTo(mImgSFR_Block(loc), mask);
        }
    }

    cv::GaussianBlur(mImgSFR_Block, mImgSFR_Block, cv::Size(3, 3), 0);
    //ShowImg("TT_ChartRes", mImgSFR_Block, 0);
}

std::string RawCreater::RawFormat_Str(format m_ft) {
    if (m_ft == format::RAW8) {
        return std::string("RAW8");
    }
    else if (m_ft == format::RAW10) {
        return std::string("RAW10");
    }
    else if (m_ft == format::RAW12) {
        return std::string("RAW12");
    }
    else if (m_ft == format::RAW16) {
        return std::string("RAW16");
    }
    else {
        return std::string("UnKnow");
    }
}

std::string RawCreater::ColorPattern_Str(colorPattern m_cp) {
    if (m_cp == colorPattern::RGGB) {
        return std::string("RGGB");
    }
    else if (m_cp == colorPattern::GRBG) {
        return std::string("GRBG");
    }
    else if (m_cp == colorPattern::GBRG) {
        return std::string("GBRG");
    }
    else if (m_cp == colorPattern::BGGR) {
        return std::string("BGGR");
    }
    else {
        return std::string("UnKnow");
    }
}

void RawCreater::normalizedColor(double* Color_vector, int nColor, int nRange, int nDL) {
    //* Target Max & Min
    int nMax_T = nColor + nRange;
    int nMin_T = nColor - nRange;

    //* Color Max & Min
    double dMax_D = std::numeric_limits<double>::min();
    double dMin_D = std::numeric_limits<double>::max();
    for (int i = 0; i < nDL; i++) {
        dMax_D = (Color_vector[i] > dMax_D) ? Color_vector[i] : dMax_D;
        dMin_D = (Color_vector[i] < dMin_D) ? Color_vector[i] : dMin_D;
    }

    if (m_ft == format::RAW8) {
        dMax_D = (dMax_D < 256) ? dMax_D : 255;
        dMin_D = (dMin_D > 0) ? dMin_D : 0;
    }
    else if (m_ft == format::RAW10) {
        dMax_D = (dMax_D < 1024) ? dMax_D : 1023;
        dMin_D = (dMin_D > 0) ? dMin_D : 0;
    }
    else if (m_ft == format::RAW12) {
        dMax_D = (dMax_D < 4096) ? dMax_D : 4095;
        dMin_D = (dMin_D > 0) ? dMin_D : 0;
    }
    else if (m_ft == format::RAW16) {
        dMax_D = (dMax_D < 65536) ? dMax_D : 65535;
        dMin_D = (dMin_D > 0) ? dMin_D : 0;
    }

    //* normalized Range
    for (int i = 0; i < nDL; i++) {
        Color_vector[i] = (Color_vector[i] - dMin_D) * (nMax_T - nMin_T) / (dMax_D - dMin_D) + nMin_T;
    }
}

void RawCreater::Image_Full(cv::Mat& _Img) {

    //* temp buffer
    cv::Mat temp = _Img(cv::Rect(0, 0, _Img.cols / 2, _Img.rows / 2)).clone();
    //* q to half
    cv::flip(temp, temp, 1);
    temp.copyTo(_Img(cv::Rect(_Img.cols / 2, 0, _Img.cols / 2, _Img.rows / 2)));
    //* hale to full
    temp.release();
    temp = _Img(cv::Rect(0, 0, _Img.cols, _Img.rows / 2)).clone();
    cv::flip(temp, temp, 0);
    temp.copyTo(_Img(cv::Rect(0, _Img.rows / 2, _Img.cols, _Img.rows / 2)));

}

void RawCreater::CreateRaw(cv::Mat& _srcImg, unsigned char* _Buffer) {

    //** color initial parameter **
    //* default RGGB
    int nS_B = 1;
    bool bS_G = false;
    //* color
    if (m_cp == colorPattern::GRBG || m_cp == colorPattern::GBRG) {
        bS_G = true;
    }
    if (m_cp == colorPattern::BGGR || m_cp == colorPattern::GBRG) {
        nS_B = -1;
    }
    //* end index
    int nEnd = 0;
    if (bS_G) {
        nEnd = 1;
    }

    //* start
    if (m_ft == format::RAW8) {
        //* buffer index
        unsigned char* dst = _Buffer;
        //* B G R B G R
        //* -1 0 1  2  3  4
        unsigned char* src = _srcImg.data + 1;
        for (size_t y = 0; y < (size_t)m_nImgH; y += 2) {
            //* boundary
            unsigned char* bayer_end = dst + m_nImgW;

            //* start with green
            if (bS_G) {
                //* G
                dst[0] = src[0];
                //* R
                dst[m_nImgW] = src[(m_nImgW * 3) + (-nS_B)];

                dst++;
                src += 3;
            }

            //* Mid
            for (; dst < bayer_end - nEnd; dst += 2, src += 6) {
                //* B G
                //* G R
                dst[0] = src[nS_B];
                dst[1] = src[0 + 3];
                dst[0 + m_nImgW] = src[(m_nImgW * 3)];
                dst[1 + m_nImgW] = src[(m_nImgW * 3) + 3 + (-nS_B)];
            }

            //* The rest
            if (nEnd == 1) {
                //* B
                dst[0] = src[nS_B];
                //* G
                dst[0 + m_nImgW] = src[(m_nImgW * 3)];

                dst++;
                src += 3;
            }

            //* to next row
            dst += m_nImgW;
            src += m_nImgW * 3;
        }
    }
    else if (m_ft == format::RAW10 || m_ft == format::RAW12 || m_ft == format::RAW16) {
        nS_B *= 2;
        nEnd *= 2;

        //* buffer index
        unsigned char* dst = _Buffer;
        //* B G R B G R
        //* -1 0 1  2  3  4
        unsigned char* src = _srcImg.data + 2;
        for (size_t y = 0; y < (size_t)m_nImgH; y += 2) {
            //* boundary
            unsigned char* bayer_end = dst + 2 * m_nImgW;

            //* start with green
            if (bS_G) {
                //* G
                dst[0] = src[0];
                dst[1] = src[1];
                //* R
                dst[(m_nImgW * 2)] = src[(m_nImgW * 6) + (-nS_B)];
                dst[(m_nImgW * 2) + 1] = src[(m_nImgW * 6) + (-nS_B) + 1];

                dst += 2;
                src += 6;
            }

            //* Mid
            for (; dst < bayer_end - nEnd; dst += 4, src += 12) {
                //* B G
                //* G R
                //* B **--
                dst[0] = src[nS_B];
                dst[1] = src[nS_B + 1];
                //* G **--
                dst[2] = src[0 + 6];
                dst[3] = src[0 + 7];
                //* G **--
                dst[0 + 2 * m_nImgW] = src[(m_nImgW * 6)];
                dst[1 + 2 * m_nImgW] = src[(m_nImgW * 6) + 1];
                //* R **--
                dst[2 + 2 * m_nImgW] = src[(m_nImgW * 6) + 6 + (-nS_B)];
                dst[3 + 2 * m_nImgW] = src[(m_nImgW * 6) + 6 + (-nS_B) + 1];
            }

            //* The rest
            if (nEnd == 2) {
                //* B
                dst[0] = src[nS_B];
                dst[1] = src[nS_B + 1];
                //* G
                dst[0 + 2 * m_nImgW] = src[(m_nImgW * 6)];
                dst[1 + 2 * m_nImgW] = src[(m_nImgW * 6) + 1];

                dst += 2;
                src += 6;
            }

            //* to next row
            dst += 2 * m_nImgW;
            src += m_nImgW * 6;
        }
    }
}

void RawCreater::SaveRaw(std::string str_name, unsigned char* _Buffer) {
    //* Save Raw
    std::fstream fsRawFile;

    fsRawFile.open(str_name + ".raw", std::fstream::out | std::fstream::binary | std::fstream::trunc);
    if (m_ft == format::RAW8) {
        fsRawFile.write((char*)_Buffer, m_nImgH * m_nImgW);
    }
    else {
        fsRawFile.write((char*)_Buffer, m_nImgH * m_nImgW * 2);
    }
    fsRawFile.close();
}

cv::Point RawCreater::rotateD(cv::Point inPoint, cv::Point centerPoint, double Dgree) {
    cv::Point result(0, 0);
    cv::Point temp(0, 0);
    double cosd = cos(Dgree * 3.141592 / 180.0);
    double sind = sin(Dgree * 3.141592 / 180.0);
    temp.x = inPoint.x - centerPoint.x;
    temp.y = inPoint.y - centerPoint.y;
    result.x = int(double(temp.x) * cosd - double(temp.y) * sind);
    result.y = int(double(temp.x) * sind + double(temp.y) * cosd);
    result.x = result.x + centerPoint.x;
    result.y = result.y + centerPoint.y;
    return result;
}
