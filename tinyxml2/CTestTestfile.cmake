# CMake generated Testfile for 
# Source directory: C:/Users/Connor/Downloads/tinyxml2-master
# Build directory: C:/Users/Connor/Desktop/tinyxml2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(xmltest "C:/Users/Connor/Desktop/tinyxml2/Debug/xmltest.exe")
  set_tests_properties(xmltest PROPERTIES  WORKING_DIRECTORY "C:/Users/Connor/Desktop/tinyxml2/Debug")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(xmltest "C:/Users/Connor/Desktop/tinyxml2/Release/xmltest.exe")
  set_tests_properties(xmltest PROPERTIES  WORKING_DIRECTORY "C:/Users/Connor/Desktop/tinyxml2/Release")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(xmltest "C:/Users/Connor/Desktop/tinyxml2/MinSizeRel/xmltest.exe")
  set_tests_properties(xmltest PROPERTIES  WORKING_DIRECTORY "C:/Users/Connor/Desktop/tinyxml2/MinSizeRel")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(xmltest "C:/Users/Connor/Desktop/tinyxml2/RelWithDebInfo/xmltest.exe")
  set_tests_properties(xmltest PROPERTIES  WORKING_DIRECTORY "C:/Users/Connor/Desktop/tinyxml2/RelWithDebInfo")
else()
  add_test(xmltest NOT_AVAILABLE)
endif()
