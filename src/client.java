import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.Scanner;
public class client {
    public static void main(String Args[]) throws SocketException, IOException{
        Scanner in = new Scanner(System.in);
        InetAddress IP = InetAddress.getByName("localhost");
        DatagramSocket clientSocket = new DatagramSocket();
        while(true) {
            byte[] sendbuffer = new byte[1024];
            byte[] receivebuffer = new byte[1024];
            System.out.print("\nClient: ");
            String clientData = in.nextLine();
            sendbuffer = clientData.getBytes();
            DatagramPacket sendPacket = new DatagramPacket(sendbuffer, sendbuffer.length, IP, 4862);
            clientSocket.send(sendPacket);
            if(clientData.equalsIgnoreCase("Bye")) {
                System.out.println("Connection ended by client");
                break;
            }
            DatagramPacket receivePacket = new DatagramPacket(receivebuffer, receivebuffer.length);
            clientSocket.receive(receivePacket);
            String serverData = new String(receivePacket.getData());
            System.out.print("\nServer: " + serverData);
        }
        clientSocket.close();
        in.close();
    }
}