# Demo
Complete sample of a Dropwizard mTLS endpoint.

Helper scripts:

1-build.sh
- builds the project

2-generate-secrets.sh
- generates a CA, server and client keypairs and certificates signed by the CA

3-run-server.sh
- runs server on port 9090, requiring client certificate signed by the generated CA

4-run-client.sh
- runs a Vanilla Java client which connects to the endpoint using its certificate
