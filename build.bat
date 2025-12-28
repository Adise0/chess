@echo off
if not exist build mkdir build
if not exist build\objects mkdir build\objects
if not exist build\sdl3.dll cp lib\SDL3\SDL3.dll build\sdl3.dll

setlocal enabledelayedexpansion

call node ./build.js

endlocal

if errorlevel 1 (
  echo Build failed.
  exit /b %errorlevel%
) else (
  echo Build succeeded. 
)

