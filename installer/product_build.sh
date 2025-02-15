#!/bin/bash
pkgbuild --root package-root \
         --identifier uk.insoft.prizmsdk \
         --version 1.0 --install-location / \
         --scripts scripts \
         prizmsdk.pkg

./update_distribution.sh
productbuild --distribution distribution.xml \
             --resources resources \
             --package-path prizmsdk.pkg \
             PrizmSDK-installer.pkg
