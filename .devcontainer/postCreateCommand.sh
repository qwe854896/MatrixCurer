#!/usr/bin/env bash

## There is now a bug for setting git credential in devcontainer ##
git config --global user.email "qwe854896@gmail.com"
git config --global user.name "Jun-Hong Cheng"
git config --global core.editor "code --wait"

## Same setup for homework environment ##
export INSTALL_PREFIX=/usr
sudo bash .devcontainer/install.sh everything
