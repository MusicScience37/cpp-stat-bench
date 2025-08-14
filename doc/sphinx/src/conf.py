"""Configuration file for Sphinx."""

# pylint: disable=invalid-name
# pylint: disable=redefined-builtin


# -- Project information -----------------------------------------------------

project = "cpp-stat-bench"
release = "unknown"  # inserted in command line

copyright = "2021, MusicScience37 (Kenta Kabashima). "
author = "MusicScience37"

# -- General configuration ---------------------------------------------------

extensions = [
    "sphinx.ext.todo",
    "sphinx_togglebutton",
]

templates_path = ["_templates"]

exclude_patterns = []

todo_include_todos = True

# -- Options for Myst-Parser -------------------------------------------------

extensions += ["myst_parser"]

myst_heading_anchors = 4

# -- Options for PlantUML ----------------------------------------------------

extensions += ["sphinxcontrib.plantuml"]

plantuml_output_format = "svg"
plantuml_syntax_error_image = True

# -- Options for breathe -----------------------------------------------------

extensions += ["breathe", "sphinx.ext.graphviz"]

# this variable must be set from command line
breathe_projects = {"stat_bench": ""}

breathe_default_project = "stat_bench"

breathe_default_members = ("members",)

breathe_domain_by_extension = {
    "h": "cpp",
}

# -- Options for HTML output -------------------------------------------------

html_theme = "sphinx_orange_book_theme"
html_static_path = ["_static"]

html_theme_options = {
    # pygment configuration must be specified here.
    "pygment_light_style": "gruvbox-light",
    "pygment_dark_style": "native",
    "repository_url": "https://gitlab.com/MusicScience37Projects/utility-libraries/cpp-stat-bench",
    "use_repository_button": True,
}
