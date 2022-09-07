:: ================ unzip file ================

"C:\Program Files\7-Zip\7z.exe" e *.tar.gz

"C:\Program Files\7-Zip\7z.exe" find . -name "*.tar" -exec 7z x "{}" -o\* \

"C:\Program Files\7-Zip\7z.exe" x *.tar -y

del *.tar


:: ================ keep *.tar.gz ================
:: del *.tar.gz



:: ================ make ================

@echo off
setlocal ENABLEDELAYEDEXPANSION

for /f "delims=" %%i in ('dir /b /s /a:-d "Makefile"') do (
  pushd "%%~dpi"
:: ================ "make" command may work on UNIX/Linux/Mac ================
:: make

  mingw32-make
  popd
)

pause