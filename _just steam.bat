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