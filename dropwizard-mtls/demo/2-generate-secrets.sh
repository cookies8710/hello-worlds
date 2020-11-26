echo -e "\n\n"
STORES=stores
PASSWORD=passphrase

# 1. clean, mkdir
if [ -d "$STORES" ]; then
	echo "Purging '$STORES'"
	rm -rf "$STORES"
fi
echo "1. creating $STORES" 
mkdir "$STORES"

pushd "$STORES"

# 2. gen CA keypair
echo "2. Generatig CA keypair"
keytool -keystore ca_store -storepass $PASSWORD -genkeypair -storetype pkcs12 -alias ca -ext bc=ca:true -dname "cn=super-duper-ca" -keyalg RSA
keytool -keystore ca_store -storepass $PASSWORD -storetype pkcs12 -list

# 3. export CA cert
echo "3. export CA cert"
keytool -keystore ca_store -storepass $PASSWORD -exportcert -storetype pkcs12 -alias ca -rfc > ca.crt

# 4. gen SERVICE keypair
echo "4. gen SERVICE keypair"
keytool -keystore server_store -storepass $PASSWORD -storetype pkcs12 -genkeypair -alias server -dname "cn=localhost" -keyalg RSA

keytool -keystore server_store -storepass $PASSWORD -storetype pkcs12 -list

# 5. import CA cert into SERVICE
echo "5. import CA cert into SERVICE"
keytool -keystore server_store -storepass $PASSWORD -storetype pkcs12 -alias ca -importcert -noprompt < ca.crt 

# 6. gen CSR for SERVICE KP
echo "6. gen CSR for SERVICE KP"
keytool -keystore server_store -storepass $PASSWORD -storetype pkcs12 -alias server -certreq -ext san=dns:localhost > server.csr

# 7. gencert for SERVICE CSR
echo "7. gencert for SERVICE CSR"
keytool -keystore ca_store -storepass $PASSWORD -gencert -storetype pkcs12 -alias ca -ext honored=all -rfc < server.csr > server.crt

# 8. import SERVICE CERT into SERVICE keystore
echo "8. import SERVICE CERT into SERVICE keystore"
keytool -keystore server_store -storepass $PASSWORD -storetype pkcs12 -alias server -importcert -noprompt < server.crt 

keytool -keystore ca_store -storepass $PASSWORD -storetype pkcs12 -list
keytool -keystore server_store -storepass $PASSWORD -storetype pkcs12 -list

# 9. client
# generate keypair, sign it by CA and append the private key
keytool -keystore client_store -storepass $PASSWORD -storetype pkcs12 -genkeypair -alias client -dname "cn=Tomas" -keyalg RSA
keytool -keystore client_store -storepass $PASSWORD -storetype pkcs12 -alias client -certreq > client.csr
keytool -keystore ca_store -storepass $PASSWORD -gencert -storetype pkcs12 -alias ca -ext honored=all -rfc < client.csr > client.crt

# import CA and signed cert to keystore so it can be used by Java Client
keytool -keystore client_store -storepass $PASSWORD -storetype pkcs12 -alias ca -importcert -noprompt < ca.crt
keytool -keystore client_store -storepass $PASSWORD -storetype pkcs12 -alias client -importcert -noprompt < client.crt

# append private key so it can be used e.g. by curl
openssl pkcs12 -in client_store -nodes -nocerts -password pass:$PASSWORD >> client.crt

echo -e "\n\n\nTo access the endpoint, first run the server and then access it either by client or:"
echo "curl --cert $(readlink -f client.crt) --cacert $(readlink -f ca.crt) https://localhost:9090/demo"
echo "openssl s_client -connect localhost:9090 -cert $(readlink -f client.crt) -CAfile $(readlink -f ca.crt)"

popd

echo "Done"
