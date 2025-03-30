# Install This Library

This library can be installed only via vcpkg currently.

## Via vcpkg

This library can be installed via [vcpkg](https://vcpkg.io/) using following configurations:

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
      "baseline": "acd5bba5aac8b6573b5f6f463dc0341ac0ee6fa4"
    },
    "registries": [
      {
        "kind": "git",
        "repository": "https://gitlab.com/MusicScience37Projects/vcpkg-registry",
        "baseline": "e9814bf742df3d99e3ef50ca9dcf8ed5d5a578c6",
        "packages": [
          "cpp-msgpack-light",
          "cpp-plotly-plotter",
          "cpp-stat-bench"
        ]
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

## Further Reading

- [Implement a Simple Benchmark](./howto/implement_simple_benchmark.md)
