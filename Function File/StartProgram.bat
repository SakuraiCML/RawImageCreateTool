set root=%~dp0%
CD /D %root%
start Raw_Creater.exe 640 480 3 1 520 896 648 100 80 -8.0 2e-6 0.0 0.0
:: 備註
:: argv[0] : .exe name
:: argv[1] : Image Width
:: argv[2] : Image Height
:: argv[3] : Image Color Patern
::   RGGB=0,
::   GRBG=1,
::   GBRG=2,
::   BGGR=3,
:: argv[4] : Image raw format
::   RAW8=0,
::   RAW10=1,
::   RAW12=2,
::   RAW16=3,
:: argv[5] : R
:: argv[6] : G
:: argv[7] : B
:: argc[8] : SFR roi width
:: argc[9] : SFR roi height
:: argc[10] : SFR rotate degree
:: argc[11] : Distortion param k1
:: argc[12] : Distortion param k2
:: argc[13] : Distortion param k3