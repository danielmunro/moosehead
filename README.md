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
$ ./run.sh mhs:latest
```

## Unordered Todos

* Grok the code.  Add documentation.
  * Core game loop.
  * OLC.
* Update gods.
* Clean up everything that is backup/outdated/not needed. Review:
  * `src/imc2-0.10`
  * `src/deity_favor_details.txt`
  * Arch-specific code, ie, `#if defined <arch>`
  * `src/o`
  * `src/quest_log*.txt`
  * `src/pload.c`
  * `**/*.eql`
* Reduce the number of compiler warnings
* GH pages -- need to define this
