

for /f "skip=1" %%x in ('wmic os get localdatetime') do if not defined mydate set mydate=%%x

rem mkdir "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
rem mkdir "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%\data"
rem xcopy /v .\*.dll "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
rem xcopy /v .\Release\bobsgame.exe "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
rem xcopy /v .\bobsgame.bmp "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
rem xcopy /v .\version.txt "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
rem xcopy /v .\README.txt "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
rem xcopy /v /e .\data "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%\data"
rem 
rem mkdir "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%\LinuxLibs"
rem xcopy /v /e .\LinuxLibs "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%\LinuxLibs"
rem xcopy /v .\bobsgameLinux "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
rem xcopy /v .\bobsgameLinux.sh "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
rem 
rem mkdir "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%\MacOSLibs"
rem xcopy /v /e .\MacOSLibs "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%\MacOSLibs"
rem xcopy /v .\bobsgameMacOS "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
rem xcopy /v .\bobsgameMacOS.sh "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
rem 
rem 
rem 7z a -tzip -mx9 -mtc=on -r "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%.zip" "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"


mkdir "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
mkdir "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%\data"
rem xcopy /v .\*.dll "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
xcopy /v .\*.dll "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
xcopy /v .\Release\bobsgame.exe "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
xcopy /v .\bobsgame.bmp "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
xcopy /v .\version.txt "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
xcopy /v .\LICENSE "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
xcopy /v /e .\data "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%\data"
7z a -tzip -mx9 -mtc=on -r "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Windows.zip" "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%"
rem 7z a -tzip -mx9 -mtc=on -r "C:\Users\Administrator\Desktop\latestWindows.zip" "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8%\*"
copy "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Windows.zip" "C:\Users\Administrator\Desktop\latestWindows.zip"

mkdir "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux"
mkdir "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux\libs"
mkdir "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux\data"
xcopy /v /e .\linux "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux\libs"
mv "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux\libs\bobsgame" "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux\bobsgame"
mv "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux\libs\bobsgame.sh" "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux\bobsgame.sh"
xcopy /v .\bobsgame.bmp "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux"
xcopy /v .\version.txt "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux"
xcopy /v .\LICENSE "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux"
xcopy /v /e .\data "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux\data"
7z a -tzip -mx9 -mtc=on -r "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux.zip" "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux"
rem 7z a -tzip -mx9 -mtc=on -r "C:\Users\Administrator\Desktop\latestLinux.zip" "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux\*"
copy "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% Linux.zip" "C:\Users\Administrator\Desktop\latestLinux.zip"

mkdir "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS"
mkdir "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS\libs"
mkdir "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS\data"
xcopy /v /e .\macos "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS\libs"
mv "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS\libs\bobsgame" "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS\bobsgame"
mv "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS\libs\bobsgame.sh" "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS\bobsgame.sh"
xcopy /v .\bobsgame.bmp "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS"
xcopy /v .\version.txt "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS"
xcopy /v .\LICENSE "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS"
xcopy /v /e .\data "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS\data"
7z a -tzip -mx9 -mtc=on -r "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS.zip" "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS"
rem 7z a -tzip -mx9 -mtc=on -r "C:\Users\Administrator\Desktop\latestMacOS.zip" "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS\*"
copy "C:\Users\Administrator\Desktop\bob's game %mydate:~0,8% MacOS.zip" "C:\Users\Administrator\Desktop\latestMacOS.zip"

xcopy /v .\version.txt "C:\Users\Administrator\Desktop"

cd "C:\Users\Administrator\Desktop"
C:\Users\Administrator\AppData\Roaming\itch\bin\butler.exe push "bob's game %mydate:~0,8% Windows.zip" bobsgame/bobs-game-puzzle-game:windows --userversion %mydate:~0,8%
C:\Users\Administrator\AppData\Roaming\itch\bin\butler.exe push "bob's game %mydate:~0,8% MacOS.zip" bobsgame/bobs-game-puzzle-game:osx --userversion %mydate:~0,8%
C:\Users\Administrator\AppData\Roaming\itch\bin\butler.exe push "bob's game %mydate:~0,8% Linux.zip" bobsgame/bobs-game-puzzle-game:linux --userversion %mydate:~0,8%

rem ftp -i -s:C:\Users\Administrator\workspace\ftp_script.txt

cd "C:\Users\Administrator\workspace\bobsgame"
rmdir /S /Q "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\"
mkdir "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content"
mkdir "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\data"
mkdir "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\windows"
mkdir "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\linux"
mkdir "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\linux\libs"
mkdir "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\macos"
mkdir "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\macos\libs"

xcopy /v /e .\data "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\data"
xcopy /v .\version.txt "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content"
xcopy /v .\LICENSE "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content"
xcopy /v .\bobsgame.bmp "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content"

xcopy /v .\*.dll "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\windows"
xcopy /v .\Release\bobsgame.exe "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\windows"

xcopy /v /e .\linux "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\linux\libs"
mv "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\linux\libs\bobsgame" "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\linux\bobsgame"
mv "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\linux\libs\bobsgame.sh" "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\linux\bobsgame.sh"

xcopy /v /e .\macos "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\macos\libs"
mv "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\macos\libs\bobsgame" "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\macos\bobsgame"
mv "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\macos\libs\bobsgame.sh" "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\content\macos\bobsgame.sh"

cd "C:\Users\Administrator\workspace\steam\steamworks_sdk_137\sdk\tools\ContentBuilder\"
run_build.bat


echo ALL DONE!!!!!!!!!!!!!!!!!!
pause