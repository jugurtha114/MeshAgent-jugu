#!/bin/sh
# Fail when a Linux agent needs a newer glibc than we promise to support.
#
# A binary built on a new glibc silently refuses to start on older distros
# ("version `GLIBC_2.38' not found"): the runner's own glibc leaks into every
# versioned symbol it links (strtol -> __isoc23_strtol, fmod@2.38, ...), and
# nothing fails until a managed device tries to install the agent.
#
# Usage: check-glibc-floor.sh <max-glibc-version> <binary>...
#   e.g. check-glibc-floor.sh 2.34 meshagent_x86-64 meshagent_x86
#
# Uses readelf, which understands every architecture we build for.
set -eu

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <max-glibc-version> <binary>..." >&2
    exit 2
fi

max=$1
shift
status=0

for bin in "$@"; do
    if [ ! -f "$bin" ]; then
        echo "FAIL  $bin: file not found" >&2
        status=1
        continue
    fi

    # The ELF version-needs table lists every GLIBC_x.y the binary depends on.
    needed=$(readelf -V "$bin" | grep -o 'Name: GLIBC_[0-9][0-9.]*' | sed 's/.*GLIBC_//' | sort -u -V)
    if [ -z "$needed" ]; then
        echo "FAIL  $bin: no GLIBC version requirements found (not a dynamic glibc binary?)" >&2
        status=1
        continue
    fi

    highest=$(printf '%s\n' "$needed" | tail -n 1)
    newest=$(printf '%s\n%s\n' "$max" "$highest" | sort -V | tail -n 1)
    if [ "$newest" = "$max" ]; then
        echo "ok    $bin: needs glibc $highest (limit $max)"
        continue
    fi

    echo "FAIL  $bin: needs glibc $highest, limit is $max. Symbols newer than $max:" >&2
    readelf --dyn-syms --wide "$bin" | grep -o '[A-Za-z0-9_]*@GLIBC_[0-9][0-9.]*' | sort -u | while read -r sym; do
        ver=${sym##*@GLIBC_}
        if [ "$(printf '%s\n%s\n' "$max" "$ver" | sort -V | tail -n 1)" != "$max" ]; then
            echo "        $sym" >&2
        fi
    done
    status=1
done

exit "$status"
