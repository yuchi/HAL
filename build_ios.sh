#!/usr/bin/env bash

# HAL
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

set -e

declare -rx VERBOSE=1
declare -r HAL_DISABLE_TESTS="ON"

cmd+="cmake"
cmd+=" -DHAL_DISABLE_TESTS=${HAL_DISABLE_TESTS}"
cmd+=" -DARCH=i386 -DPLATFORM=iphonesimulator"
#cmd+=" -DARCH=arm64 -DPLATFORM=iphoneos"

declare -r CMAKE_BUILD_TYPE=Debug
declare -r BUILD_DIR=build.$(echo ${CMAKE_BUILD_TYPE} | tr '[:upper:]' '[:lower:]')
cmd+=" -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}"
cmd+=" ../"
cmd+=" && make -j 4"

function echo_and_eval {
    local -r cmd="${1:?}"
    echo "${cmd}" && eval "${cmd}"
}

echo_and_eval "rm -rf \"${BUILD_DIR}\""
echo_and_eval "mkdir -p \"${BUILD_DIR}\""
echo_and_eval "pushd \"${BUILD_DIR}\""
echo_and_eval "${cmd}"

echo_and_eval "popd"
