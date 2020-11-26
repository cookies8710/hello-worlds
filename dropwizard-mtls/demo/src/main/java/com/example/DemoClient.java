package com.example;

import org.apache.http.ssl.SSLContexts;

import javax.net.ssl.SSLContext;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.security.KeyStore;
import java.security.cert.Certificate;
import java.security.cert.CertificateFactory;

public class DemoClient
{
    public void run(File trustedCertFile, File clientKeyStore, String clientKeyStorePassword) throws Exception {
        HttpClient httpClient = HttpClient.newBuilder().sslContext(createSslContext(trustedCertFile, clientKeyStore, clientKeyStorePassword)).build();
        HttpRequest request = HttpRequest.newBuilder(new URI("https://localhost:9090/demo?text=ECHO")).GET().build();
        HttpResponse<String> resp= httpClient.send(request, HttpResponse.BodyHandlers.ofString());
        System.out.println(resp.body());
    }

    private SSLContext createSslContext(File trustedCertificateFile, File clientKeyStoreFile, String clientKeyStorePassword) {
        try
        {
            KeyStore trustStore = KeyStoreCreator.fromCertificate(trustedCertificateFile);
            KeyStore clientKeyStore = KeyStoreCreator.fromKeystore(clientKeyStoreFile, clientKeyStorePassword);
            return SSLContexts.custom()
                    .loadKeyMaterial(clientKeyStore, clientKeyStorePassword.toCharArray(), null)
                    .loadTrustMaterial(trustStore, null).build();
        }
        catch (Exception e)
        {
            throw new RuntimeException(e);
        }
    }

    static class KeyStoreCreator
    {
        static KeyStore fromKeystore(File file, String password)
        {
            try
            {
                return KeyStore.getInstance(file, password.toCharArray());
            }
            catch (Exception e)
            {
                throw new RuntimeException(e);
            }
        }

        static KeyStore fromCertificate(File file)
        {
            try
            {
                KeyStore keyStore = KeyStore.getInstance(KeyStore.getDefaultType());

                keyStore.load(null);
                CertificateFactory certificateFactory = CertificateFactory.getInstance("X.509");
                Certificate[] certificates;
                try (InputStream input = new FileInputStream(file))
                {
                    certificates = certificateFactory.generateCertificates(input).toArray(new Certificate[0]);
                }
                for (int i = 0; i < certificates.length; i++)
                    keyStore.setCertificateEntry("certificate" + i, certificates[i]);

                return keyStore;
            }
            catch (Exception e)
            {
                throw new RuntimeException(e);
            }
        }
    }
}
