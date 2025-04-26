# Moosehead MUD: A Multi-User Dungeon Game Engine with Modern Infrastructure

Moosehead is a feature-rich MUD (Multi-User Dungeon) game engine that combines classic DikuMUD gameplay with modern infrastructure and development practices. It provides a robust foundation for text-based multiplayer gaming with support for character classes, spells, combat, clans, and extensive customization options.

The project builds upon the DikuMUD/Merc codebase while adding significant enhancements including Docker containerization, automated testing, continuous integration, and a RESTful HTTP API. Key features include:

- Complete MUD game engine with support for combat, magic, skills, and character progression
- Clan system with halls, skills, and alliances
- Extensive spell system with over 200 spells and effects
- Live editing (OLC) capabilities for game content
- Modern HTTP API for external integrations
- Docker-based development and deployment workflow
- A small collection of unit tests
- CI workflow and production deployment workflow
- Automated offsite backups for all data (players, areas, notes, etc)
- Comprehensive [item list](https://docs.google.com/spreadsheets/d/1ZtGP1EvX6mS6D_E57067qJYIVuVS6fQpzZF7GdRK9vA/edit?gid=918610314#gid=918610314) with filtering and sorting

## How to Play

A production version of the game is available at `ruinsofmidgaard.com:4000`.  To play via telnet:

```
telnet ruinsofmidgaard.com 4000
```

## Repository Structure
```
.
├── src/                    # Core game engine source code
│   ├── act_*.c/h          # Character action implementations
│   ├── magic.c/h          # Spell system implementation
│   ├── clan.c/h           # Clan system implementation
│   ├── db.c/h             # Database and data loading
│   ├── http.c/h           # HTTP API implementation
│   └── Makefile           # Build configuration
├── test/                   # Test suite
│   ├── *_test.c           # Unit tests for core components
│   └── Makefile           # Test build configuration
├── bin/
│   └── mhs                # CLI tool for managing the server
├── Dockerfile             # Production container definition
├── Dockerfile-test        # Test container definition
└── areas.txt              # Directions to all walkable areas
```

## MHS CLI

A CLI is provided for doing common development and operations tasks.

```
COMMANDS:
backup       Create a backup of MHS data
dev_reload   Build the current source and reload the running container [aliases: dev-reload]
test         Run the tests
prod_build   Build a production image [aliases: prod-build]
reload       Stop the running container and start a new one
prod_deploy  Deploy a production image [aliases: prod-deploy]
```

## Local Development

Docker is only supported way to build and run locally. Use the `mhs` CLI to build and run a container:

```
$ ./bin/mhs dev-reload
```

## HTTP API

The HTTP API is currently read-only.  Available endpoints are:

- `GET /` -- retrieve a list of endpoints
- `GET /build` -- get the current game build version
- `GET /players` -- list of online players
- `GET /races` -- list of playable races
- `GET /classes` -- list of playable classes
- `GET /help?query=<topic>` -- search help for <topic>

## Unordered Todos

* Update gods
* Remove non-unix-architecture code -- partially done
* GitHub pages
* DevOps
  * Restore from backup (dev & prod)
* Add command to get build version information
* Issues
  * VNUM data errors on startup
  * Move function declarations out of merc.h into respective .h files
  * Replace local function declarations at the top of files with including the header where possible
  * `str_cmp` re-implemented in db.c
  * `skill_lookup` move from `magic.c` -> `skills.c`
  * `slot_lookup` move from `magic.c` -> `db.c`
  * `clear_string` move out of `live_edit.c`
  * Many source files need a lot of includes... is there a better organization strategy?
