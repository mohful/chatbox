import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.Scanner;
public class server {
    public static void main(String Args[]) throws SocketException, IOException {
        DatagramSocket serverSocket = new DatagramSocket(4862);
        Scanner in = new Scanner(System.in);
        while(true) {
            byte[] receivebuffer = new byte[1024];
            byte[] sendbuffer = new byte[1024];
            DatagramPacket recpkd = new DatagramPacket(receivebuffer, receivebuffer.length);
            serverSocket.receive(recpkd);
            InetAddress IP = recpkd.getAddress();
            int port = recpkd.getPort();
            String clientdata = new String(recpkd.getData());
            System.out.println("\nClient :" + clientdata);
            System.out.print("\nServer: ");
            String serverData = in.nextLine();
            sendbuffer = serverData.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendbuffer, sendbuffer.length, IP, port);
            serverSocket.send(sendPacket);
            if(serverData.equalsIgnoreCase("Bye")) {
                System.out.println("Connection ended by Server");
                break;
            }
        }
        serverSocket.close();
        in.close();
    }
}