# rampWeights
Node for Autodesk Maya to control blend shape weights or weighted deformers with an axis based ramp for various effects.

The ramp weights node gives fast access to splitting blend shape targets or weighted deformers along any axis.
The split can be controlled by a number of attributes defining the split width and position which even can be used for animation effects. Each ramp weights node allows for controlling any number of deformers. The resulting deformer weights can be inverted, either globally or individually per output. For advanced control it's possible to create a placement node or even use a custom control to refine the split.
When disconnecting the ramp weights node from a deformer or even deleting it you can choose between keeping the generated weights or discard them.
The ramp weights node also has a couple of presets to create centered or mirrored results which cater for a greater variety of effects.

Overview on Vimeo: [rampWeights](https://vimeo.com/311842397)

The open source release of the plug-in is mainly to give people easier access to the node without having to fully commit to using the blend shape editor SHAPES.

**_Important SHAPES Note:_**
_The rampWeights node is also part of the [SHAPES](http://www.braverabbit.com/shapes/) plug-in, our advanced blend shape editor for Maya. If you have the SHAPES Blend Shape Editor installed it's not necessary to download this newer version of the plug-in.
Please see the section **SHAPES Information** at the bottom of this document._

**rampWeights is under the terms of the MIT License**

## Installation

For ease of use all files are combined as a module. This allows for an easy installation and keeps all necessary files in one location.

**_Important:_**

**_If after the installation the plug-in doesn't show up in the plug-in manager it's possible that the downloaded files from github have faulty user permissions. In this case try to create the modules folder manually and check the permissions or download the file from [braverabbit](http://www.braverabbit.com/rampweights/)._**

Copy the module folder from the repository to your Maya preferences. The module is version independent which means it can be installed in the preferences root folder.

The Maya preferences root directory is located at:

    Windows: C:\Users\USERNAME\Documents\maya
    macOS: /Users/USERNAME/Library/Preferences/Autodesk/maya
    Linux: /home/USERNAME/maya

A default Maya installation doesn't have a modules folder at this specified path. You can directly use the folder from the repository. If the modules folder already exists copy the contents of the repository's modules folder to the one in your preferences.

Inside the modules folder, rename the module template file, which matches your operating system, by removing the current extension. The file should be named rampWeights.mod.

Edit the file in a text editor and replace USERNAME in the paths with your user name. Save the file.

Restart Maya. The default Deform menus of the main Maya menu bar should now contain the menu item Edit Ramp Weights at the bottom.

## Usage

When properly installed the default Deform menus of the main Maya menu bar contain the menu item Edit Ramp Weights at the bottom.

All controls in the editor feature tooltips.
Select the node in the Attribute Editor to edit the ramp curve.

## Quick Guide

**Setup**

    - Open the editor by choosing Main Menu > Deform > Edit Ramp Weights.
    - Select the blend shape channel from the channel box or deformer which should be controlled.
    - Press the Add Node button at the top right of the editor.
        - The ramp weights node gets created and is set to be the current node in the editor in the drop-down list.
        - The deformer folder lists the connected blend shape channel or deformer.
        - The attribute folder shows the attributes of the selected ramp weights node.
    - Adjust the attributes to control the weighting effect.

**Add Output**

    - Select one or more blend shape channels by selecting these in the channel box or select one or more deformers.
    - Press the Add Deformer button at the bottom of the deformer folder.

**Additional Options**

    - RMB the ramp weights option menu to select the node or delete it. When deleting you can choose either to keep the generated weights or discard them.
    - RMB the name of the controlled deformer in the deformer folder to select the deformer.
    - Buttons for each deformer output (left to right):
        - Invert
        - Add Transform: Creates a locator which can be used to place the effect. RMB to connect a custom transform, disconnect or delete. When a transform is connected use this button to select it.
        - Disconnect and keeping the weights.
        - Disconnect and removing the weights.

## Attributes

**Axis** The axis of the ramp controlling the weights.

**Range Start** Start position of the blend along the current axis.

**Range End** End position of the blend along the current axis.

**Offset** Reposition the blending by shifting the start and end values.

**Mirror** Mirror across the current axis. Range Start, Range End and Offset then control the ramp in positive axis direction which is mirrored to the negative axis direction.

**Centered** Centers the midpoint of the ramp. Set Range Start to 0 and use Range End to control the width.

**Clamp** Prevents the blend start to cross the symmetry axis when mirroring.

**Invert** Invert the global weight values.

**Use Transform** Set to on to have the transformation of the mesh affect the position the ramp. This automatically connects the mesh transform to the ramp weights node. Note: This automatic connection is not performed when toggling the state from the channel box.

**Multiply** General scale value for the entire effect.

### Latest version: 3.0.0 (2019-01-19)

## SHAPES Information
The rampWeights node was previously only part of the SHAPES blend shape editor, though available for free to provide distributable scenes without licensing ties.
If you have SHAPES installed it's not necessary to download this open source version of the plug-in. Even though the feature set has changed slightly it doesn't affect or improve the functionality of SHAPES.
However, it is possible to replace the current version of the plug-in included with SHAPES with the updated version.
Starting with version 3.0.0 (the first open source release) the node handles the connected world matrix of the deformed mesh a bit differently than previous versions. This doesn't affect meshes which are centered in the world.
For non-centered meshes please check the resulting effect.
The next version of SHAPES will include the updated version of the rampWeights node.

## Changelog

**3.0.0 (2019-01-19)**

    - Initial open source release.
    - Better performance than previous versions.
    - New standalong editor for easier access without SHAPES.
    - Now fully supports multiple blend shape channels or deformers with one node.
    - The transform of the deformed mesh now connects to a new worldMatrix attribute. In previous versions it has been connected to the matrixList array attribute. There is a slight chance that setups created with previous versions of the plug-in produce slightly different results after the update.
    - New Use Transform attribute to include the transformation of the mesh for the result.
    - Changed the default interpolation for the curve ramp presets.
