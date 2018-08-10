#!/bin/bash

set -x 

sw5cc -host  -c -msimd simd_test.c
sw5cc -hybrid  simd_test.o -o simd_test

