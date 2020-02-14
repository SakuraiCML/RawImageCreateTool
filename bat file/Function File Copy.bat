set srcdir="%~dp0../Function File/"
set dstdir1="%~dp0../x86/Debug/"
set dstdir2="%~dp0../x86/Release/"
set dstdir3="%~dp0../x64/Debug/"
set dstdir4="%~dp0../x64/Release/"
robocopy %srcdir% %dstdir1% /e /COPY:DAT /xo
robocopy %srcdir% %dstdir2% /e /COPY:DAT /xo
robocopy %srcdir% %dstdir3% /e /COPY:DAT /xo
robocopy %srcdir% %dstdir4% /e /COPY:DAT /xo