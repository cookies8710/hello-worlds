import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.time.Instant;
import java.util.List;
import javax.net.ssl.SSLServerSocketFactory;

public class Tls
{
	public static void main(String[] argv) throws Exception
	{
		String keyStore = System.getProperty("javax.net.ssl.keyStore");
		if (keyStore == null)
			throw new RuntimeException("keystore missing");

		System.out.println("Using keystore: " + keyStore);

		SSLServerSocketFactory sslServerSocketFactory = (SSLServerSocketFactory)SSLServerSocketFactory.getDefault();
		ServerSocket serverSocket = sslServerSocketFactory.createServerSocket(8080);

		System.out.println("Now you can access the endpoint, e.g.\n\n\tcurl -k https://127.1:8080");
		int n = 0;
		while (true)
		{
			Socket client = serverSocket.accept();
			System.out.println(String.format("[%s] A client connected", Instant.now()));
			PrintWriter pw = new PrintWriter(client.getOutputStream(), true);

			String message = String.format("(%s) Secure hello #%d!", Instant.now(), ++n);

			for (String line : List.of(
				"HTTP/1.0 200 bla\r\n",
				"Content-Type: text/plain\r\n",
				"Server-name: asdf\r\n",
				"Content-Length: " + message.length() + "\r\n\r\n",
				message
			))
			    pw.print(line);
			pw.flush();
			client.close();
		}
	}
}
