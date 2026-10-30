#!/bin/bash

cut -d'|' -f"$2" "$1" | grep -v '^$' | sort | uniq
