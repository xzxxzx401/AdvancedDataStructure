#!/usr/bin/env python
# -*- coding: utf-8 -*-

from lib_builder import LibBuilder
import os


class googletestBuilder(LibBuilder):
    def __init__(self, update, force):
        super(googletestBuilder, self).__init__('googletest', update, force)

    def _dir_exist(self):
        return os.path.isdir("./googletest/.git")

    def _clone_command(self):
        return "git clone git://github.com/google/googletest.git && "\
                "cd googletest && "\
                "git reset --hard release-1.8.1"

    def _update_command(self):
        return "cd googletest && "\
                "git fetch --all && "\
                "git reset --hard release-1.8.1"

    def _lib_exist(self):
        return os.path.isfile("./googletest/output/lib/libgtest.a")

    def _make_command(self):
        return "CUR_PATH=`pwd` && "\
                "cd googletest && "\
                "mkdir -p output && "\
                "cmake -DCMAKE_INSTALL_PREFIX=${CUR_PATH}/googletest/output && "\
                "make -j 4 && "\
                "make install"
