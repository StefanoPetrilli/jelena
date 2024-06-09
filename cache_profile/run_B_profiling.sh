#!/bin/sh

perforator -e ll-read-accesses  \
           -r BInsertValues \
           -r BContainsValues \
           -r BMixedInsertContain \
           -o b_tree.txt \
           --summary ./b_tree_cache
