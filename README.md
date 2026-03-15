Core structure for this repo is derived from wjakob's [nanobind documentation](https://github.com/wjakob/nanobind) and [nanobind_example](https://github.com/wjakob/nanobind_example).

## Workflow for local development

From the documentation, `editable.rebuild=true` instructs scikit-build to rebuild the package on every import.

```
# Once
pip install nanobind scikit-build-core[pyproject] pytest
pip install --no-build-isolation --config-settings=editable.rebuild=true -ve .

# Repeat
pytest
```