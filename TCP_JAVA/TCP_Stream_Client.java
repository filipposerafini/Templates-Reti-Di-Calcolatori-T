// Filippo Serafini
// 0000723678
// TCP_Stream_Client.java

import java.net.*;
import java.io.*;

public class TCP_Stream_Client {

    public static void main(String[] args) throws IOException {

        InetAddress addr = null;
        int port = -1;

        // controllo arogmenti
        try {
            if (args.length == 2) {
                addr = InetAddress.getByName(args[0]);
                port = Integer.parseInt(args[1]);
            } else {
                System.out.println("Usage: java TCP_Stream_Client serverIP serverPort");
                System.exit(1);
            }
        } catch (UnknownHostException e) {
            System.out.println("Problemi durante la determinazione dell'endpoint del server : ");
            e.printStackTrace();
            System.exit(1);
        } catch (NumberFormatException e) {
            System.out.println("Usage: java TCP_Stream_Client serverIP serverPort");
            System.out.println("serverPort deve essere un intero");
            System.exit(1);
        }

        // dichiarazione e creazione socket
        Socket socket = null;
        DataInputStream inSock = null;
        DataOutputStream outSock = null;
        try {
            socket = new Socket(addr, port);
            socket.setSoTimeout(30000);
            System.out.println("Creata la socket: " + socket);
        } catch (Exception e) {
            System.out.println("Problemi durante la creazione della socket: ");
            e.printStackTrace();
            System.exit(1);
        }
        try {
            inSock = new DataInputStream(socket.getInputStream());
            outSock = new DataOutputStream(socket.getOutputStream());
        } catch (Exception e) {
            System.out.println("Problemi durante la creazione degli stream: ");
            e.printStackTrace();
            System.exit(1);
        }

        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        String richiesta;

        // comunicazione
        try {
            System.out.print("\n------------------------------------\nRICHIESTA, EOF per terminare: ");
            while ((richiesta = stdIn.readLine()) != null) {

                // TODO LOGICA DEL CLIENT

                System.out.print("\n------------------------------------\nRICHIESTA, EOF per terminare: ");
            } 
        } catch (IOException e) {
            System.out.println("Errore durante la cominicazione: ");
            e.printStackTrace();
            socket.close();
            System.exit(1);
        }
    }
}
