#=============================================================================
#   CMake build system files
#
#   Copyright (c) 2015 pocl developers
#
#   Permission is hereby granted, free of charge, to any person obtaining a copy
#   of this software and associated documentation files (the "Software"), to deal
#   in the Software without restriction, including without limitation the rights
#   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#   copies of the Software, and to permit persons to whom the Software is
#   furnished to do so, subject to the following conditions:
#
#   The above copyright notice and this permission notice shall be included in
#   all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#   THE SOFTWARE.
#
#=============================================================================

set(TS_NAME "PyOpenCL")
set(TS_BASEDIR "${TESTSUITE_BASEDIR}/${TS_NAME}")
set(TS_BUILDDIR "${TS_BASEDIR}/src/${TS_NAME}-build")
set(TS_SRCDIR "${TESTSUITE_SOURCE_BASEDIR}/${TS_NAME}")

# see README on how to install PyOpenCL

# TODO this will need some tweaks for proper setup. For now:
#   mkdir & cd ${TESTSUITE_BASEDIR}/PyOpenCL/src/PyOpenCL-build
# then execute the steps from the README.

if (EXISTS "${TS_BUILDDIR}/mypy/bin/py.test" AND
    IS_DIRECTORY "${TS_BUILDDIR}/pyopencl/test")

  message(STATUS "Enabling testsuite ${TS_NAME}")
  list(APPEND ACTUALLY_ENABLED_TESTSUITES "${TS_NAME}")
  set(ACTUALLY_ENABLED_TESTSUITES ${ACTUALLY_ENABLED_TESTSUITES} PARENT_SCOPE)

  add_test(NAME "PyOpenCL"
           COMMAND cd "${TS_BUILDDIR}" && source mypy/bin/activate && cd pyopencl/test &&
           PYOPENCL_NO_CACHE=1 PYOPENCL_TEST=portable py.test -v --tb=native)

  set_tests_properties("PyOpenCL"
    PROPERTIES
      LABELS "PyOpenCL")

else()

  message(STATUS "Disabling testsuite ${TS_NAME}, required files not found" )

endif()
