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
      "baseline": "80d54ff62d528339c626a6fbc3489a7f25956ade"
    },
    "registries": [
      {
        "kind": "git",
        "repository": "https://gitlab.com/MusicScience37Projects/vcpkg-registry",
        "baseline": "46060da35ec1438c424d2c7a5a49ffa0b4447d1d",
        "packages": ["cpp-msgpack-light", "cpp-stat-bench"]
      }
    ]
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
