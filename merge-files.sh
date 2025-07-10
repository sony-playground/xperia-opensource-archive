#!/bin/bash

find . -type f -name *.part00 | while read -r part; do
  base=${part%.part00}
  cat ${base}.part* > $base
done
