# CMake generated Testfile for 
# Source directory: /home/user/XCreator/vendor/bzip2-master/tests
# Build directory: /home/user/XCreator/vendor/bzip2-master/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(compress_sample1.ref "/usr/bin/python3.9" "/home/user/XCreator/vendor/bzip2-master/tests/runtest.py" "--mode" "compress" "/home/user/XCreator/vendor/bzip2-master/build/bzip2" "-1" "/home/user/XCreator/vendor/bzip2-master/tests/sample1.ref" "/home/user/XCreator/vendor/bzip2-master/tests/sample1.bz2")
set_tests_properties(compress_sample1.ref PROPERTIES  _BACKTRACE_TRIPLES "/home/user/XCreator/vendor/bzip2-master/tests/CMakeLists.txt;16;add_test;/home/user/XCreator/vendor/bzip2-master/tests/CMakeLists.txt;0;")
add_test(compress_sample2.ref "/usr/bin/python3.9" "/home/user/XCreator/vendor/bzip2-master/tests/runtest.py" "--mode" "compress" "/home/user/XCreator/vendor/bzip2-master/build/bzip2" "-2" "/home/user/XCreator/vendor/bzip2-master/tests/sample2.ref" "/home/user/XCreator/vendor/bzip2-master/tests/sample2.bz2")
set_tests_properties(compress_sample2.ref PROPERTIES  _BACKTRACE_TRIPLES "/home/user/XCreator/vendor/bzip2-master/tests/CMakeLists.txt;16;add_test;/home/user/XCreator/vendor/bzip2-master/tests/CMakeLists.txt;0;")
add_test(compress_sample3.ref "/usr/bin/python3.9" "/home/user/XCreator/vendor/bzip2-master/tests/runtest.py" "--mode" "compress" "/home/user/XCreator/vendor/bzip2-master/build/bzip2" "-3" "/home/user/XCreator/vendor/bzip2-master/tests/sample3.ref" "/home/user/XCreator/vendor/bzip2-master/tests/sample3.bz2")
set_tests_properties(compress_sample3.ref PROPERTIES  _BACKTRACE_TRIPLES "/home/user/XCreator/vendor/bzip2-master/tests/CMakeLists.txt;16;add_test;/home/user/XCreator/vendor/bzip2-master/tests/CMakeLists.txt;0;")
add_test(decompress_sample1.ref "/usr/bin/python3.9" "/home/user/XCreator/vendor/bzip2-master/tests/runtest.py" "--mode" "decompress" "/home/user/XCreator/vendor/bzip2-master/build/bzip2" "-1" "/home/user/XCreator/vendor/bzip2-master/tests/sample1.ref")
set_tests_properties(decompress_sample1.ref PROPERTIES  _BACKTRACE_TRIPLES "/home/user/XCreator/vendor/bzip2-master/tests/CMakeLists.txt;35;add_test;/home/user/XCreator/vendor/bzip2-master/tests/CMakeLists.txt;0;")
add_test(decompress_sample2.ref "/usr/bin/python3.9" "/home/user/XCreator/vendor/bzip2-master/tests/runtest.py" "--mode" "decompress" "/home/user/XCreator/vendor/bzip2-master/build/bzip2" "-2" "/home/user/XCreator/vendor/bzip2-master/tests/sample2.ref")
set_tests_properties(decompress_sample2.ref PROPERTIES  _BACKTRACE_TRIPLES "/home/user/XCreator/vendor/bzip2-master/tests/CMakeLists.txt;35;add_test;/home/user/XCreator/vendor/bzip2-master/tests/CMakeLists.txt;0;")
add_test(decompress_sample3.ref "/usr/bin/python3.9" "/home/user/XCreator/vendor/bzip2-master/tests/runtest.py" "--mode" "decompress" "/home/user/XCreator/vendor/bzip2-master/build/bzip2" "-3" "/home/user/XCreator/vendor/bzip2-master/tests/sample3.ref")
set_tests_properties(decompress_sample3.ref PROPERTIES  _BACKTRACE_TRIPLES "/home/user/XCreator/vendor/bzip2-master/tests/CMakeLists.txt;35;add_test;/home/user/XCreator/vendor/bzip2-master/tests/CMakeLists.txt;0;")
