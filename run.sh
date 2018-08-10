#!/bin/bash


set -x


bsub -I -q q_sw_expr -n 1 -cgsp 64 ./simd_test
