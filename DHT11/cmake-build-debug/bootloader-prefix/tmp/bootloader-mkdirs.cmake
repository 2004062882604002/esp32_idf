# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Espressif/frameworks/esp-idf-v5.3/components/bootloader/subproject"
  "D:/BaiduSyncdisk/Esp32/DHT11/cmake-build-debug/bootloader"
  "D:/BaiduSyncdisk/Esp32/DHT11/cmake-build-debug/bootloader-prefix"
  "D:/BaiduSyncdisk/Esp32/DHT11/cmake-build-debug/bootloader-prefix/tmp"
  "D:/BaiduSyncdisk/Esp32/DHT11/cmake-build-debug/bootloader-prefix/src/bootloader-stamp"
  "D:/BaiduSyncdisk/Esp32/DHT11/cmake-build-debug/bootloader-prefix/src"
  "D:/BaiduSyncdisk/Esp32/DHT11/cmake-build-debug/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/BaiduSyncdisk/Esp32/DHT11/cmake-build-debug/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/BaiduSyncdisk/Esp32/DHT11/cmake-build-debug/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()