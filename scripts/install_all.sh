#!/bin/bash

echo '---- Installing project dependencies'
./install_boost.sh && \
./install_wx.sh && \
./install_wxformbuilder.sh
