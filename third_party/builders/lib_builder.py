#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os
import commands
import platform


class LibBuilder(object):
    def __init__(self, name, update, force):
        self.name = name
        self.update = update
        self.force = force
        self.dependencies = set()

    def _info(self, message):
        print '\033[94m'+'INFO:  '+message+'\033[0m'

    def _fatal(self, message):
        print '\033[91m'+'FATAL: '+message+'\033[0m'
        sys.exit(-1)

    def _dir_exist(self):
        raise NotImplementedError

    def _clone_command(self):
        raise NotImplementedError

    def _update_command(self):
        raise NotImplementedError

    def _lib_exist(self):
        raise NotImplementedError

    def _make_command(self):
        raise NotImplementedError

    def _check_run(self):
        return True

    def _run(self):
        self._info('--- Building {}... ---'.format(self.name))
        if not self._check_run():
            return

        if not self._dir_exist():
            self._info('{} repository doesn\'t exist, cloning...'.format(self.name))
            s, o = commands.getstatusoutput(self._clone_command())
            if s != 0:
                self._fatal("Failed to clone {} repository\n{}".format(self.name, o))
            self._info("Finished cloning {} repository".format(self.name))
        if self.update:
            self._info("Force updating {} repository".format(self.name))
            s, o = commands.getstatusoutput(self._update_command())
            if s != 0:
                self._fatal("Failed to update {} repository\n{}".format(self.name, o))
            self._info("{} repository updated".format(self.name))
        if not self.update and not self.force and self._lib_exist():
            self._info("{} has already been built, do nothing".format(self.name))
            return
        self._info("Start building {}...".format(self.name))
        s, o = commands.getstatusoutput(self._make_command())
        if s != 0:
            self._fatal("Failed to build {} repository\n{}".format(self.name, o))
        self._info("Finished building {}".format(self.name))
