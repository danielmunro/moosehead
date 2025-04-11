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
* Reduce the number of compiler warnings
* GitHub pages
* Clean up duplicate code/functions
  * str_dup/str_dup_perm
* Implement stdbool.h, remove `typedef unsigned char bool` in merc.h
