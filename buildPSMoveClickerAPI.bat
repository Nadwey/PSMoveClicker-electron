@echo off
cd PSMoveClickerApi
call npx node-gyp configure rebuild
cd ..
pause