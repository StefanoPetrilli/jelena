#!/bin/sh

perforator -e ll-read-accesses \
           -r COBMixedInsertContain \
           -r COBInsertValues \
           -r COBContainsValues \
           -o cob_tree.txt \
           --summary ./cob_tree_cache
