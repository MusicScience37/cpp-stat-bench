Conventions
=================

Tools
-----------

This project uses following linters:

- `clang-tidy <https://clang.llvm.org/extra/clang-tidy/>`_ for C++.

This project uses following formatters:

- `clang-format <https://clang.llvm.org/docs/ClangFormat.html>`_ for C++,
- `cmake-format <https://github.com/cheshirekow/cmake_format>`_ for CMake.

This project uses following tools for documentation:

- `Doxygen <https://www.doxygen.nl/index.html>`_,
- `Sphinx <https://www.sphinx-doc.org/>`_.

This project uses following tools for dependency management:

- `Pipenv <https://pipenv.pypa.io/en/latest/>`_ (Python),

  - Update ``Pipfile.lock`` using command ``pipenv lock --keep-outdated``.

- `Conan <https://conan.io/>`_ (C++).

  - Install ``conan`` command using Pipenv.
