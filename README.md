# RawImageCreateTool
簡易Raw圖檔生成工具

# 關於本專案
- 專案內含OpenCV 4.1.1環境
- 使用Visual Studio 2019建置，可建立x86、x64環境

# 程式目的
- 生成平板式Raw圖，可輸入RGB value、Raw Type、Color Type、Image W&H

# 使用說明
- 簡易使用步驟
- 步驟1 : 開啟【Release Version / Release-V1.0.0.1】資料夾。
- 步驟2 : 以Notepad++或其他記事本軟件開啟StartProgram.bat，依據需求修改參數
- 步驟3 : 雙擊執行StartProgram.bat，結果存於SaveImg。

- 完整使用步驟
- 步驟1 : 開啟【bat file】資料夾，執行Function File Copy.bat (會複製【Function File】資料夾的圖檔至工作目錄內)，有要使用的圖檔可以放置在【Function File】資料夾內。
- 步驟2 : 開啟 VS2019 編譯exe，並輸入所需命令引數。
- 步驟3 : 執行編譯，結果存於SaveImg。

# Error Code
- 0  : Successfully End
- -1 : Not enough parameter input
- -2 : RGB setting range error
- -3 : Image showing error

# argv list
- argv[0] : .exe name
- argv[1] : Image Width
- argv[2] : Image Height
- argv[3] : Image Color Patern
-   RGGB=0,
-   GRBG=1,
-   GBRG=2,
-   BGGR=3,
- argv[4] : Image raw format
-   RAW8=0,
-   RAW10=1,
-   RAW12=2,
-   RAW16=3,
- argv[5] : R value
- argv[6] : G value
- argv[7] : B value

*歡迎大家使用!! Eric.CM.Liu*
