#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/X11Coin.ico

convert ../../src/qt/res/icons/tedcoin-16.png ../../src/qt/res/icons/tedcoin-32.png ../../src/qt/res/icons/X11Coin-48.png ${ICON_DST}
