#!/usr/bin/env python3
"""Render template.
"""

from typing import Any, Dict
from pathlib import Path
from math import log10

from aiohttp import web


THIS_DIR = Path(__file__).absolute().parent

TEMPLATES_DIR = (THIS_DIR.parent) / "src" / "stat_bench" / "reporter" / "template"

routes = web.RouteTableDef()


def render_template(name: str, params: Dict[str, Any]) -> str:
    """Render a template.

    Args:
        name (str): Template name.
        params (Dict[str, Any]): Parameters.

    Returns:
        str: Rendering result.
    """

    with open(str(TEMPLATES_DIR / name), mode="r") as file:
        contents = file.read()
    for key, val in params.items():
        contents = contents.replace(key, str(val))
    return contents


@routes.get("/line2d")
async def get_line2d(_: web.Request) -> web.Response:
    return web.Response(
        body=render_template(
            "line2d.html",
            {
                "{{PLOT_NAME}}": "Test Line",
                "{{X_TITLE}}": "x axis",
                "{{X_TYPE}}": "-",
                "{{Y_TITLE}}": "y axis",
                "{{Y_TYPE}}": "log",
                '"{{DATA}}"': """
                [
                    {
                      x: [0, 1, 2, 3, 4],
                      y: [1, 5, 3, 7, 5],
                      mode: "lines",
                      type: "scatter",
                      name: "a",
                    },
                    {
                      x: [1, 2, 3, 4, 5],
                      y: [4, 1, 4, 6, 8],
                      mode: "lines",
                      type: "scatter",
                      name: "b",
                    },
                ]
            """,
            },
        ),
        content_type="html",
    )


@routes.get("/violin")
async def get_violin(_: web.Request) -> web.Response:
    return web.Response(
        body=render_template(
            "violin.html",
            {
                "{{PLOT_NAME}}": "Test Violin",
                "{{Y_TITLE}}": "y axis",
                "{{Y_TYPE}}": "log",
                '"{{Y_MIN}}"': str(log10(0.5)),
                '"{{Y_MAX}}"': str(log10(10)),
                '"{{DATA}}"': """
                [
                    {
                        y: [1, 5, 3, 7, 5],
                        type: "violin",
                        name: "x1",
                        box: {
                            visible: true,
                        },
                        meanline: {
                            visible: true,
                        },
                        points: "outliers",
                    },
                    {
                        y: [4, 1, 4, 6, 8],
                        type: "violin",
                        name: "x2",
                        box: {
                            visible: true,
                        },
                        meanline: {
                            visible: true,
                        },
                        points: "outliers",
                    },
                ]
            """,
            },
        ),
        content_type="html",
    )


app = web.Application()
app.add_routes(routes)
web.run_app(app)
