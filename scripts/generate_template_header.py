#!/usr/bin/env python3
"""Helper script to generate C++ header files of HTML templates.
"""

import pathlib
import typing

import click

THIS_DIR = pathlib.Path(__file__).absolute().parent
ROOT_DIR = THIS_DIR.parent
TEMPLATE_DIR = ROOT_DIR / "src" / "stat_bench" / "plots" / "template"

TEMPLATE_SUFFIX = ".jinja"


def collect_templates() -> typing.List[pathlib.Path]:
    """Collect path of templates."""
    return [path for path in TEMPLATE_DIR.iterdir() if path.suffix == TEMPLATE_SUFFIX]


def generate_header_contents(template_path: pathlib.Path) -> None:
    """Generate contents of a C++ header file."""
    with open(str(template_path), mode="r", encoding="utf8") as file:
        html_contents = file.read()

    relative_template_path = template_path.relative_to(ROOT_DIR)
    var_name = template_path.stem
    return f"""/*
 * Copyright 2023 MusicScience37 (Kenta Kabashima)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*!
 * @file
 * @brief Definition of {var_name} variable.
 *
 * This header is automatically generated from
 * {relative_template_path}.
 * Change this file only via scripts/generate_template_header.py script.
 */
#pragma once

namespace stat_bench {{
namespace reporter {{

/*!
 * @brief Contents of file
 * {relative_template_path}.
 */
static constexpr const char* {var_name} = R"({html_contents})";

}}  // namespace reporter
}}  // namespace stat_bench
"""


def load_current_contents_if_exists(path: pathlib.Path) -> typing.Optional[str]:
    """Load current contents of a file if possible."""
    try:
        with open(str(path), mode="r", encoding="utf8") as file:
            return file.read()
    except Exception:
        return None


def generate_template_header(template_path: pathlib.Path) -> None:
    """Generate a C++ header file of an HTML template."""
    header_path = template_path.parent / f"{template_path.stem}.h"
    header_contents = generate_header_contents(template_path)
    if load_current_contents_if_exists(header_path) == header_contents:
        return
    with open(str(header_path), mode="w", encoding="utf8") as file:
        file.write(header_contents)


@click.command()
@click.argument("template_paths", nargs=-1)
def main(template_paths: typing.List[str]) -> None:
    """Generate C++ header files of HTML templates."""
    template_path_objs = [pathlib.Path(path).absolute() for path in template_paths]
    if not template_path_objs:
        template_path_objs = collect_templates()
    for path in template_path_objs:
        generate_template_header(path)


if __name__ == "__main__":
    main()
