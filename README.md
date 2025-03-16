# Moosehead

Moosehead SLED, haphazardly updated from the original source.  Requires docker.
Use the following to run:

```
$ docker build . -t mhs:latest
$ ./run.sh mhs:latest
```

## Changelog

### 2025-03-15

* Fixed the Dockerfile so now a new container can be created and connected to.
* Copied external dependencies into `deps/` for future-proofing.
* Merged `ubuntu-15.04` into the main branch, fixed a handful of conflicts.  This likely caused a regression or two somewhere, but starting with a clean, single, long-lived branch is worth it in the long run.
* Added a CI pipeline to build and push a docker image.  Pushing to `ghcr.io/danielmunro/moosehead`.  Versions are the sha of the commit to the main branch that triggered the build.
* An instance is up and running at `ruinsofmidgaard.com:4000`.

## Unordered Todos

* Grok the code.  Add documentation.
  * Core game loop.
  * OLC
* Organize data assets (`player`, `area`, `gods`, `jail`, `jerks`).
  * Put under a `data` directory.
  * Convert to a docker volume.
  * Create an offsite backup strategy.
* Update gods.
* Clean up everything that is backup/outdated/not needed. Review:
  * `backup/`
  * `players_pre_IMM/`
  * `cvsroot/`
  * `src/imc2-0.10`
  * `src/deity_favor_details.txt`
  * Arch-specific code, ie, `#if defined <arch>`
  * `src/o`
  * `src/quest_log*.txt`
  * `src/pload.c`
  * `clan/`
  * `**/*.eql`
  * `utils/`
