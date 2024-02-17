# Installation

## Via vcpkg

This library can be installed via vcpkg using following configurations:

- Add a vcpkg registry
  `https://gitlab.com/MusicScience37Projects/vcpkg-registry`
  in `vcpkg-configuration.json`.

  Example:

  ```json
  {
    "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg-tool/main/docs/vcpkg-configuration.schema.json",
    "default-registry": {
      "kind": "git",
      "repository": "https://github.com/Microsoft/vcpkg",
      "baseline": "13bde2ff13192e1b2fdd37bd9b475c7665ae6ae5"
    },
    "registries": [
      {
        "kind": "git",
        "repository": "https://gitlab.com/MusicScience37Projects/vcpkg-registry",
        "baseline": "70fb6d7d9d95ad17fc02dc4aef839b9a4824ac23",
        "packages": ["cpp-msgpack-light", "cpp-stat-bench"]
      }
    ],
    "overlay-triplets": ["./vcpkg_conf/triplets"]
  }
  ```

- Add `cpp-stat-bench` in `vcpkg.json`

  Example:

  ```json
  {
    "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg-tool/main/docs/vcpkg.schema.json",
    "dependencies": ["cpp-stat-bench"]
  }
  ```
