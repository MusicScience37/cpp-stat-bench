#!/bin/bash

set -e

cd $(dirname $(dirname $0))

mkdir -p doc/sphinx/src/schema/docs

poetry run jsonschema2md schemas/data_file_schema_v1.json doc/sphinx/src/schemas/docs/data_file_schema_v1.md
