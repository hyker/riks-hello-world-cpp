@echo off
setlocal enableextensions enabledelayedexpansion

if defined VCInstallDir (
    rem Change compiler if applicable
    if not ["%VSCMD_ARG_TGT_ARCH%"]==["x64"] (
        set "CWD=%cd%"
        
        set VCVARSALL="%VCInstallDir%vcvarsall.bat"
        if not exist !VCVARSALL! set VCVARSALL="%VCInstallDir%Auxiliary\Build\vcvarsall.bat"
        if not exist !VCVARSALL! (
            echo Can't find vcvarsall.bat.
            goto :eof
        )

        call !VCVARSALL! x64

        if not errorlevel 0 goto :eof
        cd /d !CWD!
    )

    if exist build rd /s /q build
    md build
    cd build

	call python ..\download.py vs2015 x64

	call cl^
	    /Iinclude^
	    ..\main.cpp^
	    riks.lib^
	    toolbox.lib^
	    /MD

	copy ..\res\default.config .
	copy ..\res\truststore.p12 .

	echo.
	echo Build complete. Running hello world...
	echo.
	call main.exe
) else (
    echo You must run this script from a Visual Studio Command Prompt.
)

endlocal