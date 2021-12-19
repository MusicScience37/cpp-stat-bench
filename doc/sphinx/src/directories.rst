Directory Structure
======================

.. uml::

    @startsalt
    {
    {T
    + cpp-stat-bench           | Root directory of this project.
    ++ cmake                    | CMake scripts.
    ++ doc                      | Documentation.
    +++ doxygen                 | Configuration of documentation generated using Doxygen.
    +++ sphinx                  | Documentation generated using Sphinx.
    ++++ src                    | Source of documentation generated using Sphinx.
    ++ examples                 | Examples.
    ++ include                  | Include directory of this library itself.
    ++ src                      | Source directory of this library itself.
    ++ scripts                  | Helper scripts in development.
    ++ tests                    | Tests.
    +++ units                   | Unit tests.
    }
    }
    @endsalt
