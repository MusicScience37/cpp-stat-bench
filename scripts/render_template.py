#!/usr/bin/env python3
"""Render template."""

import json
from math import log10
from pathlib import Path
from typing import Any, Dict

import jinja2
from aiohttp import web

THIS_DIR = Path(__file__).absolute().parent

TEMPLATES_DIR = (THIS_DIR.parent) / "src" / "stat_bench" / "plots" / "template"

routes = web.RouteTableDef()


def escape_for_html(input: str) -> str:
    temp = input
    temp = temp.replace("&", "&amp;")
    temp = temp.replace("<", "&lt;")
    temp = temp.replace(">", "&gt;")
    temp = temp.replace('"', "&quot;")
    temp = temp.replace("'", "&#x27;")
    return temp


jinja2_env = jinja2.Environment(loader=jinja2.FileSystemLoader(str(TEMPLATES_DIR)))
# Use custom function for escapes to use the same algorithm as in C++.
jinja2_env.globals["escape_for_html"] = escape_for_html


@routes.get("/line2d")
async def get_line2d(_: web.Request) -> web.Response:
    return web.Response(
        body=jinja2_env.get_template("plotly_plot.jinja").render(
            title="Test Line",
            dataset=json.dumps(
                {
                    "data": [
                        {
                            "x": [0, 1, 2, 3, 4],
                            "y": [1, 5, 3, 7, 5],
                            "mode": "lines",
                            "type": "scatter",
                            "name": "a",
                        },
                        {
                            "x": [1, 2, 3, 4, 5],
                            "y": [4, 1, 4, 6, 8],
                            "mode": "lines",
                            "type": "scatter",
                            "name": "b",
                        },
                    ],
                    "layout": {
                        "title": "Test Line &<>'\"",
                        "xaxis": {
                            "title": "x axis",
                            "type": "-",
                        },
                        "yaxis": {
                            "title": "y axis",
                            "type": "log",
                        },
                        "showlegend": True,
                    },
                    "config": {
                        "scrollZoom": True,
                        "responsive": True,
                    },
                }
            ),
        ),
        content_type="html",
    )


@routes.get("/violin")
async def get_violin(_: web.Request) -> web.Response:
    return web.Response(
        body=jinja2_env.get_template("plotly_plot.jinja").render(
            title="Test Line",
            dataset=json.dumps(
                {
                    "data": [
                        {
                            "y": [1, 5, 3, 7, 5],
                            "type": "violin",
                            "name": "x1",
                            "box": {
                                "visible": True,
                            },
                            "meanline": {
                                "visible": True,
                            },
                            "points": "outliers",
                        },
                        {
                            "y": [4, 1, 4, 6, 8],
                            "type": "violin",
                            "name": "x2",
                            "box": {
                                "visible": True,
                            },
                            "meanline": {
                                "visible": True,
                            },
                            "points": "outliers",
                        },
                    ],
                    "layout": {
                        "title": "Test Line &<>'\"",
                        "xaxis": {
                            "title": "x axis",
                            "type": "-",
                        },
                        "yaxis": {
                            "title": "y axis",
                            "type": "log",
                            "constrain": "range",
                            "range": [log10(0.5), log10(10)],
                        },
                        "showlegend": True,
                    },
                    "config": {
                        "scrollZoom": True,
                        "responsive": True,
                    },
                }
            ),
        ),
        content_type="html",
    )


app = web.Application()
app.add_routes(routes)
web.run_app(app)
