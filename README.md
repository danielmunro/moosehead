# Moosehead

Moosehead SLED, haphazardly updated from the original source.  

To play this iteration of Moosehead:

```
telnet ruinsofmidgaard.com 4000
```

# Development

Requires docker to run locally. Use the helper `run.sh`:

```
$ docker build . -t mhs:latest
$ ./bin/run.sh mhs:latest
```

## Unordered Todos

* Update gods
* Remove non-unix-architecture code
  * Partially done
* GitHub pages
* DevOps
  * Deploy to prod from laptop
  * Restore from backup (dev & prod)
* Add command to get build version information
* Issues
  * `convert.c` mentioned a function, `spec_guard`, but that function doesn't exist.  Using `spec_guard_d` instead.
  * Refactor `alloc_perm` -> 'GC_MALLOC'
  * VNUM data errors on startup
  * Move function declarations out of merc.h into respective .h files
  * Replace local function declarations at the top of files with including the header where possible
  * `str_cmp` re-implemented in db.c
  * `skill_lookup` move from `magic.c` -> `skills.c`
  * `slot_lookup` move from `magic.c` -> `db.c`
  * `clear_string` move out of `live_edit.c`
  * Many source files need a lot of includes... is there a better organization strategy?
