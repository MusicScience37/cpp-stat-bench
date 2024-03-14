"""Scrubbers in approvaltests."""

import re

import approvaltests.scrubbers


def scrub_current_time(input: str) -> str:
    return re.sub(
        r"\d\d\d\d-\d\d-\d\dT\d\d:\d\d:\d\d\.\d\d\d\d\d\d[+-]\d\d\d\d",
        "<time>",
        input,
    )


def _scrub_float_impl(input: str) -> str:
    return "1." + "0" * (len(input) - 2)


def scrub_float(input: str) -> str:
    return re.sub(
        r"\d+\.\d+([eE][+-]\d+)?",
        lambda match: _scrub_float_impl(match.group(0)),
        input,
    )


def _scrub_integer_with_comma_impl(input: str) -> str:
    return "0" * (len(input) - 4) + ",000"


def scrub_integer_with_comma(input: str) -> str:
    return re.sub(
        r"\d+,\d\d\d",
        lambda match: _scrub_integer_with_comma_impl(match.group(0)),
        input,
    )


scrub_console = approvaltests.scrubbers.combine_scrubbers(
    scrub_current_time, scrub_float, scrub_integer_with_comma
)
