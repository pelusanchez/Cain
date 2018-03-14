#!/bin/bash
g++ \
color/hsv.cpp \
EasyBMP.cpp \
utils.cpp \
main.cpp \
data.cpp \
color/image.cpp \
filter/filter_gaussian_blur.cpp \
filter/filter_hipass.cpp \
filter/filter_transmission_map.cpp \
filter/filter_blur.cpp \
filter/filter_unsharp.cpp \
filter/filter_histogram.cpp \
filter/filter_darkest.cpp \
filter/filter_graytocolor.cpp \
filter/filter_contrast_stretch_cumulative.cpp \
filter/filter_rx_falsecolor.cpp \
macros/dehaze.cpp \
macros/histogram.cpp \
macros/contrast.cpp \
-std=c++11 -o main