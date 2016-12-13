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

        // TODO VARIABILI PER LA LOGICA DEL PROGRAMMA
        String richiesta = null;
        String esito = null;

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

        // invio richiesta e chiusura socket lato output
        try {
            // TODO INTERAZIONE CON L'UTENTE E INVIO RICHIESTA (esempio stringa)
            outSock.writeUTF(richiesta);
            socket.shutdownOutput();
            System.out.println("Trasmissione terminata.");
        } catch (IOException e) {
            System.out.println("Errore durante l'invio della richiesta: ");
            e.printStackTrace();
            socket.close();
            System.exit(1);
        }

        // ricezione esito e chiusura socket lato input
        try {
            // TODO RICEZIONE ESITO (esempio stringa)
            esito = inSock.readUTF();
            System.out.println("Esito: " + esito);
            socket.shutdownInput();
            System.out.println("Terminata chiusura della socket: " + socket);
        } catch (SocketTimeoutException ste) {
            System.out.println("Timeout scattato: ");
            ste.printStackTrace();
            socket.close();
            System.exit(1);
        } catch (IOException e) {
            System.out.println("Errore durante la ricezione dell'esito: ");
            e.printStackTrace();
            socket.close();
            System.exit(1);
        }
    }
}
