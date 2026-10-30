#!/bin/bash

find "$1" -name ".keep" -exec git rm {} \;
