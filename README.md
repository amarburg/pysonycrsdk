Core structure for this repo is derived from wjakob's [nanobind documentation](https://github.com/wjakob/nanobind) and [nanobind_example](https://github.com/wjakob/nanobind_example).

## Workflow for local development

```
pip install nanobind scikit-build-core[pyproject] pytest
pip install --no-build-isolation -ve . -Ceditable.rebuild=true

pytest 
```