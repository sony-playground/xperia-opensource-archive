#!/bin/sh
sphinx-build -b latex . _doc_build/pdf && \
make -C _doc_build/pdf all-pdf && \
find _doc_build/pdf -type f ! -name '*.pdf' -delete && \
find _doc_build/pdf -type f -name 'plantuml*' -delete

sphinx-build -E -b html . _doc_build/files/fcs
