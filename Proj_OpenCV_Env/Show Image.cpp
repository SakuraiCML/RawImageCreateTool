#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// warning disable
#pragma warning(disable : 26495)
#pragma warning(disable : 6011)
#pragma warning(disable : 26439)
#pragma warning(disable : 6269)
#pragma warning(disable : 26451)
#pragma warning(disable : 6294)
#pragma warning(disable : 6201)

//Raw Creater
#include "RawCreater.h"

int main(int argc, char* argv[]) {

    //* Call Class RawCreater
    RawCreater rcObj(argc, argv);

    //* Initial
    int nErrorCode = rcObj.Initial();
    if (nErrorCode != 0) {
        system("pause");
        return nErrorCode;
    }

    //* Create RAW
    rcObj.CreateRawImg();
    //rcObj.ShowImg("TT_G_S", rcObj.mImg, 0);

    //* Create SFR Chess Chart
    rcObj.SFRChessChart(rcObj.m_sfrW, rcObj.m_sfrH, rcObj.m_sfrDegree);

    //* Create SFR Cross Chart
    rcObj.SFRCrossChart(rcObj.m_sfrW, rcObj.m_sfrH, rcObj.m_sfrDegree);

    //* Create SFR Block Chart
    rcObj.SFRBlockChart(rcObj.m_sfrW, rcObj.m_sfrH, rcObj.m_sfrDegree);

    //* SaveImage
    std::string strFileName = std::to_string(rcObj.m_nImgW) + "_" +
        std::to_string(rcObj.m_nImgH) + "_" +
        rcObj.ColorPattern_Str(rcObj.m_cp) + "_" +
        rcObj.RawFormat_Str(rcObj.m_ft);          
    rcObj.SaveImg(strFileName);
    
    //* Show Result
    if (!rcObj.ShowImg(0)) {
        system("pause");
        return -3;
    }

    //system("pause");
    return 0;
}