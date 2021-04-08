# ----------------------------------------------------------------------
# userSetup.mel
#
# Automatically add the menu items for the weights controller nodes upon
# Maya startup.
#
# ----------------------------------------------------------------------

from maya import cmds, mel, utils

import inspect, os

def addMenuItems():
    if not cmds.about(batch=True):
        mel.eval("source brWeightsControllerCreateMenuItems; brWeightsControllerAddMenuCommand;")
        # Get the path of this setup file and store the parent path
        # as the module's content path. This is needed to get access
        # to the preset files and the plug-in path.
        scripts = os.path.dirname(os.path.realpath(inspect.getfile(inspect.currentframe())))

        scripts = scripts.replace("\a", "/a")
        scripts = scripts.replace("\b", "/b")
        scripts = scripts.replace("\f", "/f")
        scripts = scripts.replace("\n", "/n")
        scripts = scripts.replace("\r", "/r")
        scripts = scripts.replace("\t", "/t")
        scripts = scripts.replace("\v", "v/")
        scripts = scripts.replace("\\", "/")

        mel.eval("optionVar -stringValue \"brWeightsControllerContentPath\" \"{}\";".format(os.path.dirname(scripts)))

utils.executeDeferred(addMenuItems)

# ----------------------------------------------------------------------
# MIT License
#
# Copyright (c) 2021 Ingo Clemens, brave rabbit
# rampWeights and weightsServer are under the terms of the MIT License
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# Author: Ingo Clemens    www.braverabbit.com
# ----------------------------------------------------------------------
