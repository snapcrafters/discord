#!/usr/bin/env bash

# This script requires:
#     apt install jq curl git

DEB_API="https://discordapp.com/api/download?platform=linux&format=deb"
DEB_URL=$(curl -w "%{url_effective}\n" -I -L -s -S "${DEB_API}" -o /dev/null)

if [ -f OLD_VERSION ]; then
    source OLD_VERSION
else
    OLD_VERSION=0
fi
REBUILD=0
HOST_ARCH=$(dpkg-architecture -q DEB_HOST_ARCH)

# Get the version from the tag_name and the download URL.
VERSION=$(echo "${DEB_URL}" | cut -d'/' -f6)
DEB=$(basename "${DEB_URL}")
rm -f snap/snapcraft.yaml.new 2>/dev/null

if [ "${OLD_VERSION}" != "${VERSION}" ]; then
    echo "Detected ${VERSION}, which is different from ${OLD_VERSION}!"
    sed "s/VVV/${VERSION}/" snap/snapcraft.yaml.in > snap/snapcraft.yaml.new
    sed -i "s|UUU|${DEB_URL}|" snap/snapcraft.yaml.new
    sed -i "s|ARCH|${DEB_ARCH}|" snap/snapcraft.yaml.new
    REBUILD=1
else
    echo "No version change, still ${OLD_VERSION}. Stopping here."
fi

if [ ${REBUILD} -eq 1 ]; then
    mv snap/snapcraft.yaml.new snap/snapcraft.yaml
    echo "OLD_VERSION=${VERSION}" > OLD_VERSION
    git commit -m "Version bumped to ${VERSION}"
    git push
fi
