# Changelog

## 2025-04-24

* Refactored out usages of `alloc_perm` and `alloc_free`, in favor of `GC_MALLOC`, and `GC_FREE`.
* There is a flag in Makefiles for building either the game version or the olc version.  This was hardcoded to the game version and had to be changed to build the olc version.  This can now be configured via the new `--olc` option in the `dev-reload` [command](https://github.com/danielmunro/moosehead/blob/992f2e16b44bfeae8d4fa16b90ac50ce529cb2e2/Argcfile.sh#L32).

## 2025-04-23

* Moved function declarations out of `merc.h` and into respective header files.

## 2025-04-18

* Added weekly and monthly backup jobs.  The current backup schedule is:
  * Daily, with a one-week retention.
  * Weekly, with a one-month retention.
  * Monthly, with a one-year retention.
* Fixed Rockbiter form to be FORM_MINERAL.

## 2025-04-17

* New race added: gnomes.  Gnomes are a race of tiny humanoids, standing no more than 3' tall on average. They are quite adept in the arts of magic, only being surpassed in raw talent by faeries.  Being a tiny race, they are also nimble on their feet, making adequate thieves. Gnomes can see in the dark with infravision.  Gnomes possess deep wisdom, leading to a desire to keep their alignment neutral. Remaining neutral gives gnomes a small bonus to their spell casting. A help entry is still on the todo list.
* Fix a bug introduced in a change that came in with the http server, causing xp to be calculated incorrectly.
* Improve CI/CD so that tests run on any branch.  Docker images are published on main after a successful test run.
* Fully implement `stdbool.h`

## 2025-04-15

* Add an http server with the following endpoints:
  * GET / - returns a list of available endpoints.
  * GET /build - get the current build version.
  * GET /races - array of races.
  * GET /classes - array of classes.
  * GET /players - array of logged in players.
  * GET /help - search for a help topic via `query` parameter.

## 2025-04-08

* Add log levels, default to `info`.

## 2025-04-07

* Switch to `main` for the default branch to match the prevailing convention for git and the maintainer's preferred name for the default branch.
* Refactor OLC menus to add a top level MENU_DATA struct, which contains the below properties.  The menu layout and column width were previously encoded within the id of the header menu item, which overloaded this variable for multiple different purposes and was confusing.
  * A layout style (ONE_COLUMN, TWO_COLUMNS)
  * A column width -- for use when the layout is set to TWO_COLUMNS
  * Menu items -- an array of selections that make up the menu

## 2025-04-06

* Fix a bug introduced when adding `dump_obj_csv.c`, where `area_first` was getting set to NULL (whoops).  Among other things, this was breaking resets.

## 2025-04-05

* Don't set the UID in the game anymore.  I'm sure this was the right call at the time, but especially now with docker builds the code should always run as root within its container.

## 2025-04-04

* Finish fixing all compiler warning.
* Add `-Werror` to compiler flags, now all compiler warnings will be treated as errors.
* Add `dev-reload.sh` helper script for easier dev-test loops.  Running `dev-reload.sh` will build the code, stop and remove the running game container, run the newly built container, and tail its logs.  

## 2025-03-30

* Add build version to the greeting screen.
* Fix a ton of compiler warnings.

## 2025-03-26

* fight.c - fix compiler warnings, format the file.

## 2025-03-25

* comm.c - fix compiler warnings, mainly wrong types, implicit declarations, and indentation.
* Add tests for `input.c`.

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