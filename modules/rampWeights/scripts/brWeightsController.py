import maya.api.OpenMaya as om2

import logging

logger = logging.getLogger(__name__)


def clearWeights(attribute):
    """Clear the deformer weights of the given attribute by assigning
    an empty array. This is much faster than iterating through all
    weights indices individually and removing them.

    :param attribute: The full path of the weights attribute which
                      should get cleared.
    :type attribute: str
    """
    sel = om2.MSelectionList()
    sel.add(attribute)
    plug = sel.getPlug(0)
    emptyArray = om2.MDoubleArray()
    dataFn = om2.MFnDoubleArrayData()
    obj = dataFn.create(emptyArray)
    plug.setMObject(obj)


def displayInfo(msg):
    """Output the given message to the command output.
    """
    logger.info(msg)

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
