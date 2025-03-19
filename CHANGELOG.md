# Changelog

## 2025-03-19

* Switched to use native docker logging behavior. `log_string` now logs to stdout, new `log_error` logs to stderr.
* Updated Dockerfile to use the executable directly, removed `area/startup` script.
* Added license files to top level directory.

## 2025-03-17

* Added a flag to generate an equipment list csv.
* Added `areas.txt` to the top level, contains directions to most areas.

## 2025-03-16

* Upgraded to the latest Ubuntu LTS release, 24.04.  Removed the dependencies that were copied in, instead use all the latest dependencies provided by `apt`.

## 2025-03-15

* Merged `ubuntu-15.04` into the main branch, fixed a handful of conflicts.  This likely caused a regression or two somewhere, but starting with a clean, single, long-lived branch is worth it in the long run.
* Fixed the Dockerfile so now a new container can be created and connected to.
* Copied external dependencies into `deps/` for future-proofing, in case those dependencies disappear from the internet.
* Added a CI pipeline to build and push a docker image.  Pushing to `ghcr.io/danielmunro/moosehead`.  Versions are the sha of the commit to the main branch that triggered the build.
* An instance is up and running.