First attempt to generate a Python wrapper for the [Sony Camera Remote SDK](https://support.d-imaging.sony.co.jp/app/sdk/en/index.html) using [nanobind](https://github.com/wjakob/nanobind)

Core structure for this repo is derived from nanobind documentation and [`nanobind_example`](https://github.com/wjakob/nanobind_example).

## Workflow for local development

From the documentation, `editable.rebuild=true` instructs scikit-build to rebuild the package on every import.

```
# Once
pip install nanobind scikit-build-core[pyproject] pytest
pip install --no-build-isolation --config-settings=editable.rebuild=true -ve .

# Repeat
pytest
```

# License

This module is released under the [MIT License](LICENSE), the underlying Sony SDK is released under their [own license](https://support.d-imaging.sony.co.jp/app/sdk/licenseagreement/en-US.html).
