# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))

# -- Project information -----------------------------------------------------

project = 'cpp-stat-bench'
release = 'unknown'  # inserted in command line

copyright = '2021, MusicScience37 (Kenta Kabashima). '
author = 'MusicScience37'

# -- General configuration ---------------------------------------------------

extensions = [
    'sphinx.ext.todo',
    'myst_parser',
]

templates_path = ['_templates']

exclude_patterns = []

# -- Options for PlantUML ----------------------------------------------------

extensions += ['sphinxcontrib.plantuml']

plantuml_output_format = 'svg'
plantuml_syntax_error_image = True

# -- Options for HTML output -------------------------------------------------

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']
