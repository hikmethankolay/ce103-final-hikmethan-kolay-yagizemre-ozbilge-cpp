#!/bin/bash
# chmod +x 7-build-app.sh
# ./7-build-app.sh

# Get the current directory path
currentDir=$(dirname "$(readlink -f "$0")")

echo "Deletion File Processed with Clean Project Script on Windows Part"

echo "Delete and Create the 'release' folder and its contents"
rm -rf "out"
rm -rf "release_linux"
rm -rf "publish_linux"
rm -rf "build_linux"
mkdir "publish_linux"
mkdir "release_linux"
mkdir "build_linux"

echo "Delete the 'docs' folder and its contents"
rm -rf "docs/coverxygenliblinux"
rm -rf "docs/coverxygentestlinux"
rm -rf "docs/coveragereportliblinux"
rm -rf "docs/coveragereporttestlinux"
rm -rf "docs/doxygenliblinux"
rm -rf "docs/doxygentestlinux"
rm -rf "docs/testresultslinux"
mkdir "docs"
mkdir "docs/coverxygenliblinux"
mkdir "docs/coverxygentestlinux"
mkdir "docs/coveragereportliblinux"
mkdir "docs/coveragereporttestlinux"
mkdir "docs/doxygenliblinux"
mkdir "docs/doxygentestlinux"
mkdir "docs/testresultslinux"

echo "create txt files for unit test"

echo "0-)TEXT STRING0" > test1.txt
echo "1-)TEXT STRING1" >> test1.txt
echo "2-)TEXT STRING2" >> test1.txt
echo "3-)TEXT STRING3" >> test1.txt
echo "4-)TEXT STRING4" >> test1.txt

echo "0-)TEXT STRING0" > test2.txt
echo "1-)TEXT STRING1" >> test2.txt
echo "2-)TEXT STRING2" >> test2.txt
echo "3-)TEXT STRING3" >> test2.txt
echo "4-)TEXT STRING4" >> test2.txt

echo "0-)TEXT STRING0" > test3.txt
echo "1-)TEXT STRING1" >> test3.txt
echo "2-)TEXT STRING2" >> test3.txt
echo "3-)TEXT STRING3" >> test3.txt
echo "4-)TEXT STRING4" >> test3.txt

echo "0-)TEXT STRING0" > test4.txt
echo "1-)TEXT STRING1" >> test4.txt
echo "2-)TEXT STRING2" >> test4.txt
echo "3-)TEXT STRING3" >> test4.txt
echo "4-)TEXT STRING4" >> test4.txt

echo "0-)TEXT STRING0" > test5.txt
echo "1-)TEXT STRING1" >> test5.txt
echo "2-)TEXT STRING2" >> test5.txt
echo "3-)TEXT STRING3" >> test5.txt
echo "4-)TEXT STRING4" >> test5.txt

echo "txt files created successfully"

echo "Delete the 'site' folder and its contents"
#rm -rf "site"
mkdir "site"

echo "Folders are Recreated successfully."

echo "Generate HTML/LATEX/RTF/XML Documentation for Library (No Source Code Only Headers)"
STRIP_FROM_PATH="$currentDir"
doxygen DoxyfileLibLinux

echo "Generate HTML/LATEX/RTF/XML Documentation for Unit Tests (Test Sources and Test Data Sets)"
doxygen DoxyfileTestLinux

echo "Not: coverxygen uses doxygen xml output for coverage"

echo "Run Documentation Coverage Data Collector for Library (No Source Code Only Headers)"
python3 -m coverxygen --xml-dir ./docs/doxygenliblinux/xml --src-dir ./ --format lcov --output ./docs/coverxygenliblinux/lcov_doxygen_lib_linux.info

echo "Run Documentation Coverage Data Collector for Unit Tests (Test Sources and Test Data Sets)"
python3 -m coverxygen --xml-dir ./docs/doxygentestlinux/xml --src-dir ./ --format lcov --output ./docs/coverxygentestlinux/lcov_doxygen_test_linux.info


echo "Run Documentation Coverage Report Generator for Library"
reportgenerator "-title:Farming Management Library Documentation Coverage Report (Linux)" "-reports:**/lcov_doxygen_lib_linux.info" "-targetdir:docs/coverxygenliblinux" "-reporttypes:Html" "-filefilters:-*.md;-*.xml;-*[generated];-*build*" "-historydir:report_doc_lib_hist_linux"
reportgenerator "-reports:**/lcov_doxygen_lib_linux.info" "-targetdir:assets/doccoverageliblinux" "-reporttypes:Badges" "-filefilters:-*.md;-*.xml;-*[generated];-*build*"

echo "Run Documentation Coverage Report Generator for Unit Tests"
reportgenerator "-title:Farming Management Library Test Documentation Coverage Report (Linux)" "-reports:**/lcov_doxygen_test_linux.info" "-targetdir:docs/coverxygentestlinux" "-reporttypes:Html" "-filefilters:-*.md;-*.xml;-*[generated];-*build*" "-historydir:report_doc_test_hist_linux"
reportgenerator "-reports:**/lcov_doxygen_test_linux.info" "-targetdir:assets/doccoveragetestlinux" "-reporttypes:Badges" "-filefilters:-*.md;-*.xml;-*[generated];-*build*"


echo "Testing Application with Coverage"
echo "Configure CMAKE"
cmake -B build_linux -DCMAKE_BUILD_TYPE=Debug -G "Ninja" -DCMAKE_INSTALL_PREFIX:PATH=publish_linux
echo "Build CMAKE Debug/Release"
cmake --build build_linux --config Debug -j4
cmake --build build_linux --config Release -j4
cmake --install build_linux --strip
echo "Test CMAKE"

cp test1.txt build_linux/src/tests/car_maintenance
cp test2.txt build_linux/src/tests/car_maintenance
cp test3.txt build_linux/src/tests/car_maintenance
cp test4.txt build_linux/src/tests/car_maintenance
cp test5.txt build_linux/src/tests/car_maintenance

cd build_linux
# ctest -C Debug -j4 --output-on-failure --output-log test_results_linux.log
ctest -C Debug -j4 --output-junit testResults_linux.xml --output-log test_results_linux.log
junit2html testResults_linux.xml testResults_linux.html
cp testResults_linux.html "../docs/testresultslinux/index.md"
cd ..

echo Running Test Executable


./publish_linux/bin/car_maintenance_tests
./publish_linux/bin/car_maintenance_app

echo "Generate Test Coverage Data"
lcov --rc lcov_branch_coverage=1 --capture --initial --directory . --output-file coverage_linux.info
lcov --rc lcov_branch_coverage=1 --capture --directory . --output-file coverage_linux.info
lcov --rc lcov_branch_coverage=1 --remove coverage_linux.info '/usr/*' --output-file coverage_linux.info
lcov --rc lcov_branch_coverage=1 --remove coverage_linux.info 'tests/*' --output-file coverage_linux.info
lcov --rc lcov_branch_coverage=1 --list coverage_linux.info

echo "Generate Test Report"
reportgenerator "-title:Farming Management Library Unit Test Coverage Report (Linux)" "-reports:**/coverage_linux.info" "-targetdir:docs/coveragereportliblinux" "-reporttypes:Html" "-sourcedirs:src/car_maintenance_lib/src;src/car_maintenance_lib/include;src/car_maintenance_app/src;src/car_maintenance_app/include;src/tests/car_maintenance" "-filefilters:-*minkernel\*;-*gtest*;-*a\_work\*;-*gtest-*;-*gtest.cc;-*gtest.h;-*build*" "-historydir:report_test_hist_linux"
reportgenerator "-reports:**/coverage_linux.info" "-targetdir:assets/codecoverageliblinux" "-reporttypes:Badges" "-sourcedirs:src/car_maintenance_lib/src;src/car_maintenance_lib/include;src/car_maintenance_app/src;src/car_maintenance_app/include;src/tests/car_maintenance" "-filefilters:-*minkernel\*;-*gtest*;-*a\_work\*;-*gtest-*;-*gtest.cc;-*gtest.h;-*build*"

echo "Copy the 'assets' folder and its contents to 'docs' recursively"
cp -R assets "docs/assets"

echo "Copy the 'README.md' file to 'docs/index.md'"
cp README.md "docs/index.md"

echo "Files and folders copied successfully."

# echo "Generate Webpage"
# mkdocs build

echo "Package Publish Linux Binaries"
tar -czvf release_linux/linux-publish-binaries.tar.gz -C publish_linux .

echo "Package Publish Linux Binaries"
mkdir -p build_linux/build/Release
cp -R src/car_maintenance_lib/include build_linux/build/Release
tar -czvf release_linux/linux-release-binaries.tar.gz -C build_linux/build/Release .

echo "Package Publish Debug Linux Binaries"
mkdir -p build_linux/build/Debug
cp -R src/car_maintenance_lib/include build_linux/build/Debug
cp test1.txt publish_linux/bin
cp test2.txt publish_linux/bin
cp test3.txt publish_linux/bin
cp test4.txt publish_linux/bin
cp test5.txt publish_linux/bin
tar -czvf release_linux/linux-debug-binaries.tar.gz -C build_linux/build/Debug .

echo "Package Publish Test Coverage Report"
tar -czvf release_linux/linux-test-coverage-report.tar.gz -C docs/coveragereportliblinux .

echo "Package Publish Library Doc Coverage Report"
tar -czvf release_linux/linux-lib-doc-coverage-report.tar.gz -C docs/coverxygenliblinux .

echo "Package Publish Unit Test Doc Coverage Report"
tar -czvf release_linux/linux-test-doc-coverage-report.tar.gz -C docs/coverxygentestlinux .

echo "Package Publish Library Documentation"
tar -czvf release_linux/linux-doxygen-lib-documentation.tar.gz -C docs/doxygenliblinux .

echo "Package Publish Unit Test Documentation"
tar -czvf release_linux/linux-doxygen-test-documentation.tar.gz -C docs/doxygentestlinux .

echo Package Publish Test Results Report
tar -czvf release_linux/linux-test-results-report.tar.gz -C docs/testresultslinux .

echo "...................."
echo "Operation Completed!"
