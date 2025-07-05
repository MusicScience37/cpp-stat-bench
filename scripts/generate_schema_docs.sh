#!/bin/bash

set -e

cd $(dirname $(dirname $0))

mkdir -p doc/sphinx/src/schema/docs

poetry run jsonschema2md schemas/data_file_schema_v1.json doc/sphinx/src/schemas/docs/data_file_schema_v1.md
poetry run jsonschema2md schemas/data_file_schema_v2.json doc/sphinx/src/schemas/docs/data_file_schema_v2.md
poetry run jsonschema2md schemas/data_file_schema_v3.json doc/sphinx/src/schemas/docs/data_file_schema_v3.md
poetry run jsonschema2md schemas/data_file_schema_v4.json doc/sphinx/src/schemas/docs/data_file_schema_v4.md
