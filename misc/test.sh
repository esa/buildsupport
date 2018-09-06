#!/bin/bash
# template test case to transform post-processed IV to png
buildsupport -test -o out -glue -gw -i InterfaceView.aadl -c DeploymentView.aadl -d DataView.aadl ./TASTE_IV_Properties.aadl ocarina_components.aadl TASTE_DV_Properties.aadl
cp out/iv2.py ./iv.py
# parameters of iv_stg are filtered as nodes from the redered graph
./iv_stg.py x86_partition_taste_api > file.dot
neato file.dot -Tpng -o iv.png
xdg-open iv.png
