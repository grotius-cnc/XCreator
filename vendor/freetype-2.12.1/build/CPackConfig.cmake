# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/home/user/XCreator/vendor/freetype-2.12.1;/home/user/XCreator/vendor/freetype-2.12.1/build")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENTS_ALL "Unspecified;headers;pkgconfig")
set(CPACK_COMPONENT_HEADERS_DEPENDS "libraries")
set(CPACK_COMPONENT_HEADERS_DESCRIPTION "C/C++ header files for use with FreeType")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C/C++ Headers")
set(CPACK_COMPONENT_HEADERS_GROUP "Development")
set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION "Library used to build programs which use FreeType")
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_LIBRARIES_GROUP "Development")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.18/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "freetype built using CMake")
set(CPACK_GENERATOR "TGZ")
set(CPACK_INSTALL_CMAKE_PROJECTS "/home/user/XCreator/vendor/freetype-2.12.1/build;freetype;ALL;/")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "/home/user/XCreator/vendor/freetype-2.12.1/builds/cmake")
set(CPACK_NSIS_DISPLAY_NAME "freetype 2.12.1")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "freetype 2.12.1")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "/home/user/XCreator/vendor/freetype-2.12.1/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/home/user/XCreator/vendor/freetype-2.12.1/README")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The FreeType font rendering library.")
set(CPACK_PACKAGE_FILE_NAME "freetype-2.12.1-Linux")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "freetype 2.12.1")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "freetype 2.12.1")
set(CPACK_PACKAGE_NAME "freetype")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Humanity")
set(CPACK_PACKAGE_VERSION "2.12.1")
set(CPACK_PACKAGE_VERSION_MAJOR "2")
set(CPACK_PACKAGE_VERSION_MINOR "12")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_RESOURCE_FILE_LICENSE "/home/user/XCreator/vendor/freetype-2.12.1/LICENSE.TXT")
set(CPACK_RESOURCE_FILE_README "/usr/share/cmake-3.18/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.18/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/user/XCreator/vendor/freetype-2.12.1/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_RPM "OFF")
set(CPACK_SOURCE_TBZ2 "ON")
set(CPACK_SOURCE_TGZ "ON")
set(CPACK_SOURCE_TXZ "ON")
set(CPACK_SOURCE_TZ "ON")
set(CPACK_SOURCE_ZIP "OFF")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_TOPLEVEL_TAG "Linux")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/user/XCreator/vendor/freetype-2.12.1/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
