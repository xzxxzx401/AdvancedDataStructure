#!/usr/bin/env python
# -*- coding: utf-8 -*-

import argparse
import sys
import os
import commands
import platform
from builders import registry


def _parse_args():
    parse = argparse.ArgumentParser(description='Build third parties')
    parse.add_argument('-l', "--lib", type=str, required=False, default='all', help="The library you'll build, default all")
    parse.add_argument('-f', "--force", action='store_true', default=False, help="force to build again")
    parse.add_argument('-u', "--update", action='store_true', default=False, help="update repository")
    return parse.parse_args()


class Runner(object):
    def __init__(self):
        self.built_libs = set()

    def build(self, lib, update, force):
        if lib in self.built_libs:
            return
        module = __import__('builders.{}_builder'.format(lib))
        builder = getattr((getattr(module, '{}_builder'.format(lib))), '{}Builder'.format(lib))(update, force)
        self.built_libs.add(lib)  # break circular dependency
        for dep in builder.dependencies:
            builder._info('dependency of {}: {}'.format(lib, dep))
            if dep in self.built_libs:
                builder._info('{} is already in built_libs, skip'.format(dep))
                continue
            self.build(dep, False, False)  # don't update denpendency?
        builder._run()

def main():
    args = _parse_args()
    libs = args.lib.split(',')
    runner = Runner()
    if 'all' in libs:
        for lib in registry.registered_libs:
            runner.build(lib, args.update, args.force)
    else:
        for lib in libs:
            runner.build(lib, args.update, args.force)


if __name__ == '__main__':
    main()
