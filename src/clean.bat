echo off
cls
if exist *.user del *.user
if exist *.ncb del *.ncb
if exist ipch rmdir ipch /s /q
if exist Debug rmdir Debug /s /q
if exist Release rmdir Release /s /q
echo - FIN DU NETTOYAGE DE LA SOLUTION !
pause
exit