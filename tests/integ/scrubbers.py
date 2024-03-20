"""Scrubbers in approvaltests."""

import re

import approvaltests.scrubbers


def scrub_current_time(input: str) -> str:
    return re.sub(
        r"\d\d\d\d-\d\d-\d\dT\d\d:\d\d:\d\d\.\d\d\d\d\d\d[+-]\d\d\d\d",
        "<time>",
        input,
    )


def _scrub_number_impl(input: str) -> str:
    if len(input) < 1:
        return input
    return " " * (len(input) - 1) + "n" + input[-1]


def scrub_float(input: str) -> str:
    return re.sub(
        r"\d+\.\d+([eE][+-]\d+)?( |,)",
        lambda match: _scrub_number_impl(match.group(0)),
        input,
    )


def scrub_integer_with_comma(input: str) -> str:
    return re.sub(
        r"\d+,\d\d\d ",
        lambda match: _scrub_number_impl(match.group(0)),
        input,
    )


def scrub_integer(input: str) -> str:
    return re.sub(
        r" \d+ ",
        lambda match: _scrub_number_impl(match.group(0)),
        input,
    )


scrub_console = approvaltests.scrubbers.combine_scrubbers(
    scrub_current_time, scrub_float, scrub_integer_with_comma, scrub_integer
)
