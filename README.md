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
* Implement stdbool.h, remove `typedef unsigned char bool` in merc.h
  * Partially done
* Backups
  * Daily - done
  * Weekly
  * Monthly
  * Yearly
* DevOps
  * Deploy to prod from dev laptop
  * Deploy to prod via GitHub workflow
  * Restore from backup (dev & prod)
* Misc. fixes
  * Rockbiters reference form `ee`, which doesn't exist.  This is likely supposed to be `dd`.
