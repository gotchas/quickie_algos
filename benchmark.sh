#!/usr/bin/env bash

sudo cpupower frequency-set --governor performance
build/bench
sudo cpupower frequency-set --governor powersave
