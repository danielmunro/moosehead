# Changelog

## 2025-03-23

* Add a test target.  Add tests for recently updated code.  Add a step in CI to run tests before building and pushing a new docker image.

## 2025-03-22

* Use a docker volume for all game data (areas, newareas, clans, players, gods, jerks, jail, olc).
* Add a backup script, since data is no longer stored in git. Currently, backup runs daily, with a retention period of one week.  Next steps will include adding weekly and monthly backups.  The entire docker volume is gzipped and uploaded to a private S3 bucket.

## 2025-03-21

* Fix an error that could lead to a buffer overflow.
  * Skill level lookup would ignore the reclass and look only at the base class, then the other base class.
  * When neither base class had access to the skill, ie for a skill like 'chi' where neither mage or warrior had access to it, but the samurai reclass did, a -1 would be returned for the level the skill is obtained.
  * This caused a buffer overflow in the 'skills' command since the string formatting uses a '%d', which is for signed integers.
  * The fix was to return the reclass level if it was greater than -1.
* Removed a few more unused resources.

## 2025-03-20

* Create a fresh CSV dump of items on every start up.  Save it to the docker data volume.
* Clean up comm.c:
  * Remove most/all commented out code.
  * Remove platform/arch specific code.  Unix will be the only supported arch going forward.

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