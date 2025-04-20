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
* Clean up duplicate code/functions
  * str_dup/str_dup_perm
* DevOps
  * Deploy to prod from laptop
  * Restore from backup (dev & prod)
* Issues
  * `convert.c` mentioned a function, `spec_guard`, but that function doesn't exist.  Using `spec_guard_d` instead.
  * Refactor `alloc_perm` -> 'GC_MALLOC'
  * VNUM data errors on startup
  * `gamble.c` not referenced in Makefile -- can it be removed?
  * `sign.c` not referenced in Makefile -- can it be removed?
  * Move function declarations out of merc.h into respective .h files
