Python Bindings for two-means trees
===================================

Python Bindings for two-means-trees(https://github.com/vstrnadova/two-means-trees).

Installation
------------

**On Unix (Linux, OS X) and MAC**

 - clone this repository
 - `pip install ./two-means-tree`

**On Windows (Requires Visual Studio 2015)**

 - For Python 3.5:
     - clone this repository
     - `pip install ./two-means-trees`
 - For earlier versions of Python, including Python 2.7:


Windows runtime requirements
----------------------------

On Windows, the Visual C++ 2015 redistributable packages are a runtime
requirement for this project. It can be found [here](https://www.microsoft.com/en-us/download/details.aspx?id=48145).

If you use the Anaconda python distribution, you may require the Visual Studio
runtime as a platform-dependent runtime requirement for you package:

```yaml
requirements:
  build:
    - python
    - setuptools
    - pybind11

  run:
   - python
   - vs2015_runtime  # [win]
```


License
-------
TODO

Test call
---------

```python
import two_means_trees as tmt
tmt.<method>
```
