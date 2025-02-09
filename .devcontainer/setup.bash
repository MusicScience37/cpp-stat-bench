#!/bin/bash

sudo chmod 0777 /cache_volume/
mkdir -p $CCACHE_DIR
mkdir -p $VCPKG_DEFAULT_BINARY_CACHE
mkdir -p $POETRY_CACHE_DIR

poetry config virtualenvs.in-project true
poetry env use 3.13
poetry sync

poetry run pre-commit install

git config commit.template .gitmessage

git config gpg.program gpg2
git config commit.gpgsign true
git config tag.gpgsign true

echo "source /usr/share/bash-completion/completions/git" >> ~/.bashrc
