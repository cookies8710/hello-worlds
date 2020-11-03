#!/usr/bin/bash

STOREFILE="test-keystore"
STOREPASS="passw0rd"
DIR=$(readlink -f "$0" | xargs dirname)
pushd "$DIR"

pwd

if [ ! -f "$STOREFILE" ]; then
	echo "Creating keystore"
	keytool -genkey -keyalg RSA -keystore "$STOREFILE" -storepass "$STOREPASS" -dname "cn=John Doe, ou=Orgunit, o=Org, c=CZ"
fi

echo "Keystore content:"
keytool -list -keystore "$STOREFILE" -storepass "$STOREPASS"

javac -d . Tls.java && java -Djavax.net.ssl.keyStore="$(readlink -f "$STOREFILE")" -Djavax.net.ssl.keyStorePassword="$STOREPASS" Tls

popd
