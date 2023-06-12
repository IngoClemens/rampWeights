**4.1.1 (2023-06-12)**
* Added support for Maya 2024.

**4.1.1 (2022-06-01)**
* Added support for Maya 2023.
* Fixed an issue related to an empty deformer component list.

**4.1.0 (2021-03-29) - Update**
* Added support for Maya 2022.

**4.1.0 (2020-03-07)**
* Added support for Maya 2020.
* Fixed that when using more than one controller source the attributes will perform with an offset resulting in a shift of the effect.

**4.0.0 (2019-08-14)**
* Added the weightsServer node to the toolset as another way of controlling deformer weights.
* General improvements with parallel evaluation.
* Added an installer for easier installation.

**3.0.0 (2019-01-19)**
* Initial open source release.
* Better performance than previous versions.
* New standalone editor for easier access without SHAPES.
* Now fully supports multiple blend shape channels or deformers with one node.
* The transform of the deformed mesh now connects to a new worldMatrix attribute. In previous versions it has been connected to the matrixList array attribute. There is a slight chance that setups created with previous versions of the plug-in produce slightly different results after the update.
* New _Use Transform_ attribute to include the transformation of the mesh for the result.
* Changed the default interpolation for the curve ramp presets.
