@echo off
@setlocal enableextensions
@cd /d "%~dp0"

rem Get the current directory path
for %%A in ("%~dp0.") do (
    set "currentDir=%%~fA"
)

::echo Clean Project
::call 9-clean-project.bat

echo Create the "release" folder and its contents
mkdir publish_win
mkdir release_win
mkdir build_win

echo Create the "docs" folder and its contents
mkdir docs
cd docs
mkdir coverxygenlibwin
mkdir coverxygentestwin
mkdir coveragereportlibwin
mkdir coveragereporttestwin
mkdir doxygenlibwin
mkdir doxygentestwin
mkdir testresultswin
cd ..

echo create bin files for unit tests

echo 0-)TEXT STRING0> test1.bin
echo 1-)TEXT STRING1>> test1.bin
echo 2-)TEXT STRING2>> test1.bin
echo 3-)TEXT STRING3>> test1.bin
echo 4-)TEXT STRING4>> test1.bin

echo 0-)TEXT STRING0> test2.bin
echo 1-)TEXT STRING1>> test2.bin
echo 2-)TEXT STRING2>> test2.bin
echo 3-)TEXT STRING3>> test2.bin
echo 4-)TEXT STRING4>> test2.bin

echo 0-)TEXT STRING0> test3.bin
echo 1-)TEXT STRING1>> test3.bin
echo 2-)TEXT STRING2>> test3.bin
echo 3-)TEXT STRING3>> test3.bin
echo 4-)TEXT STRING4>> test3.bin

echo 0-)TEXT STRING0> test4.bin
echo 1-)TEXT STRING1>> test4.bin
echo 2-)TEXT STRING2>> test4.bin
echo 3-)TEXT STRING3>> test4.bin
echo 4-)TEXT STRING4>> test4.bin

echo 0-)TEXT STRING0> test5.bin
echo 1-)TEXT STRING1>> test5.bin
echo 2-)TEXT STRING2>> test5.bin
echo 3-)TEXT STRING3>> test5.bin
echo 4-)TEXT STRING4>> test5.bin

echo bin files created successfully

echo Create the "site" folder and its contents
mkdir site

echo Folders are Recreated successfully.

echo Generate Documentation

set STRIP_FROM_PATH=%currentDir%

echo Generate HTML/LATEX/RTF/XML Documentation for Library (No Source Code Only Headers)
call doxygen DoxyfileLibWin

echo Generate HTML/LATEX/RTF/XML Documentation for Unit Tests (Test Sources and Test Data Sets)
call doxygen DoxyfileTestWin

echo Not: coverxygen uses doxygen xml output for coverage

echo Run Documentation Coverage Data Collector for Library (No Source Code Only Headers)
call python -m coverxygen --xml-dir ./docs/doxygenlibwin/xml --src-dir ./ --format lcov --output ./docs/coverxygenlibwin/lcov_doxygen_lib_win.info

echo Run Documentation Coverage Data Collector for Unit Tests (Test Sources and Test Data Sets)
call python -m coverxygen --xml-dir ./docs/doxygentestwin/xml --src-dir ./ --format lcov --output ./docs/coverxygentestwin/lcov_doxygen_test_win.info
rem call python -m coverxygen --xml-dir ./docs/doxygen/xml --src-dir ./ --format lcov --output ./docs/coverxygen/lcov.info --prefix %currentDir%\

rem echo Run lcov genhtml
rem call perl C:\ProgramData\chocolatey\lib\lcov\tools\bin\genhtml --legend --title "Documentation Coverage Report" ./docs/coverxygen/lcov.info -o docs/coverxygen

echo Run Documentation Coverage Report Generator for Library 
call reportgenerator "-title:Car Maintenence Library Documentation Coverage Report (Windows)" "-reports:**/lcov_doxygen_lib_win.info" "-targetdir:docs/coverxygenlibwin" "-reporttypes:Html" "-filefilters:-*.md;-*.xml;-*[generated];-*build*" "-historydir:report_doc_lib_hist_win"
call reportgenerator "-reports:**/lcov_doxygen_lib_win.info" "-targetdir:assets/doccoveragelibwin" "-reporttypes:Badges" "-filefilters:-*.md;-*.xml;-*[generated];-*build*"

echo Run Documentation Coverage Report Generator for Unit Tests 
call reportgenerator "-title:Car Maintenence Library Test Documentation Coverage Report (Windows)" "-reports:**/lcov_doxygen_test_win.info" "-targetdir:docs/coverxygentestwin" "-reporttypes:Html" "-filefilters:-*.md;-*.xml;-*[generated];-*build*" "-historydir:report_doc_test_hist_win"
call reportgenerator "-reports:**/lcov_doxygen_test_win.info" "-targetdir:assets/doccoveragetestwin" "-reporttypes:Badges" "-filefilters:-*.md;-*.xml;-*[generated];-*build*"

echo Testing Application with Coverage
echo Configure CMAKE
call cmake -B build_win -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 17 2022" -DCMAKE_INSTALL_PREFIX:PATH=publish_win
echo Build CMAKE Debug/Release
call cmake --build build_win --config Debug -j4
call cmake --build build_win --config Release -j4
rem call cmake --install build_win --strip
start "Install Debug" cmake --install build_win --config Debug --strip
start "Install Release" cmake --install build_win --config Release --strip

copy test1.bin build_win\src\tests\car_maintenance
copy test2.bin build_win\src\tests\car_maintenance
copy test3.bin build_win\src\tests\car_maintenance
copy test4.bin build_win\src\tests\car_maintenance
copy test5.bin build_win\src\tests\car_maintenance

echo Test CMAKE
cd build_win
:: Test are already run with OpenCppCoverage...
::call ctest -C Debug -j4 --output-on-failure --output-log test_results_windows.log
call ctest -C Debug -j4 --output-junit testResults_windows.xml --output-log test_results_windows.log
call junit2html testResults_windows.xml testResults_windows.html
call copy testResults_windows.html "..\docs\testresultswin\index.html"
cd ..

echo Generate Test Coverage Data for Car Mainteanace Lib
call OpenCppCoverage.exe --export_type=binary:car_maintenance_tests_unit_win.cov --sources src\car_maintenance_lib\src --sources src\car_maintenance_lib\include --sources src\tests\car_maintenance -- build_win\build\Debug\car_maintenance_tests.exe

echo Generate Test Coverage Data for Car Mainteanace App and Combine Results
call OpenCppCoverage.exe --input_coverage=car_maintenance_tests_unit_win.cov --export_type=cobertura:car_maintenance_app_unit_win_cobertura.xml --sources src\car_maintenance_lib\src --sources src\car_maintenance_lib\include --sources src\car_maintenance_app\src --sources src\car_maintenance_app\include --sources src\tests\car_maintenance -- build_win\build\Debug\car_maintenance_app.exe

echo Generate Unit Test Coverage Report
call reportgenerator "-title:Car Maintenence Library Unit Test Coverage Report (Windows)" "-targetdir:docs/coveragereportlibwin" "-reporttypes:Html" "-reports:**/car_maintenance_app_unit_win_cobertura.xml" "-sourcedirs:src/car_maintenance_lib/src;src/car_maintenance_lib/include;src/car_maintenance_app/src;src/car_maintenance_app/include;src/tests/car_maintenance" "-filefilters:-*minkernel\*;-*gtest*;-*a\_work\*;-*gtest-*;-*gtest.cc;-*gtest.h;-*build*" "-historydir:report_test_hist_win"
call reportgenerator "-targetdir:assets/codecoveragelibwin" "-reporttypes:Badges" "-reports:**/car_maintenance_app_unit_win_cobertura.xml" "-sourcedirs:src/car_maintenance_lib/src;src/car_maintenance_lib/include;src/car_maintenance_app/src;src/car_maintenance_app/include;src/tests/car_maintenance" "-filefilters:-*minkernel\*;-*gtest*;-*a\_work\*;-*gtest-*;-*gtest.cc;-*gtest.h;-*build*"

echo Copy the "assets" folder and its contents to "docs" recursively
call robocopy assets "docs\assets" /E

echo Copy the "README.md" file to "docs\index.md"
call copy README.md "docs\index.md"

echo Files and folders copied successfully.

:: echo Generate Webpage
:: call mkdocs build

rem echo Publish Linux Binaries
rem call dotnet publish -c Release -r linux-x64 --self-contained true -o publish/linux

rem echo Publish MacOS Binaries
rem call dotnet publish -c Release -r osx-x64 --self-contained true -o publish/macos

rem echo Publish Windows Binaries
rem call dotnet publish -c Release -r win-x64 --self-contained true -o publish/windows

rem echo Package Linux Binaries
rem call tar -czvf release/linux-binaries.tar.gz -C publish/linux .

rem echo Package MacOS Binaries
rem call tar -czvf release/macos-binaries.tar.gz -C publish/macos .

echo Package Publish Windows Binaries
tar -czvf release_win\windows-publish-binaries.tar.gz -C publish_win .

echo Package Publish Windows Binaries
call robocopy src\car_maintenance_lib\include "build_win\build\Release" /E
call robocopy src\car_maintenance_app\include "build_win\build\Release" /E
tar -czvf release_win\windows-release-binaries.tar.gz -C build_win\build\Release .

echo Package Publish Debug Windows Binaries
call robocopy src\car_maintenance_lib\include "build_win\build\Debug" /E
call robocopy src\car_maintenance_app\include "build_win\build\Debug" /E

copy test1.bin publish_win\bin
copy test2.bin publish_win\bin
copy test3.bin publish_win\bin
copy test4.bin publish_win\bin
copy test5.bin publish_win\bin

tar -czvf release_win\windows-debug-binaries.tar.gz -C build_win\build\Debug .

echo Package Publish Test Coverage Report
tar -czvf release_win\windows-test-coverage-report.tar.gz -C docs\coveragereportlibwin .

echo Package Publish Library Doc Coverage Report
tar -czvf release_win\windows-lib-doc-coverage-report.tar.gz -C docs\coverxygenlibwin .

echo Package Publish Unit Test Doc Coverage Report
tar -czvf release_win\windows-test-doc-coverage-report.tar.gz -C docs\coverxygentestwin .

echo Package Publish Library Documentation
tar -czvf release_win\windows-doxygen-lib-documentation.tar.gz -C docs\doxygenlibwin .

echo Package Publish Unit Test Documentation
tar -czvf release_win\windows-doxygen-test-documentation.tar.gz -C docs\doxygentestwin .

echo Package Publish Test Results Report
tar -czvf release_win\windows-test-results-report.tar.gz -C docs\testresultswin .

echo ....................
echo Operation Completed!
echo ....................
pause



