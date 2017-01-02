#!/bin/bash

echo '-- Installing wxFormBuilder'
sudo add-apt-repository -y ppa:wxformbuilder/release && \
sudo apt-get update && \
sudo apt-get install wxformbuilder
