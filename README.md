# s21_decimal
Implementation of own s21_decimal library.

## Subject

- [Subject EN](./docs/subject_en.md)
- [Subject RU](./docs/subject_ru.md)

## Solution

`$> make s21_decimal.a` to build library.

`$> make tests && ./tests` to run unit tests using libcheck.

`$> make gcov_report` to build coverage report using lcov. Report in `gcov_report/index.html`.

`$> sh ./tests/scripts/run.sh` to run docker conteiner with tests.

The `./tests/code_examples/` directory contains code examples for generating tests of the Decimal class in C#.
