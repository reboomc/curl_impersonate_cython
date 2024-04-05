@rd /S /Q build

d:\Python38-32\python.exe setup.py build_ext -i
if "%ERRORLEVEL%" EQU "0" (
    rem do_what_u_want
)