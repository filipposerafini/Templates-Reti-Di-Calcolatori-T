// Filippo Serafini
// 0000723678
// UDP_Unicast_Server.java

import java.io.*;
import java.net.*;

public class UDP_Unicast_Server {

    private static final int PORT = 54321;

    public static void main(String[] args) {
        int port = -1;

        // controllo argomenti
        if (args.length == 0) {
            port = PORT;
            System.out.println("porta: " + PORT);
        } else if (args.length == 1) {
            try {
                port = Integer.parseInt(args[0]);
                if (port < 1024 || port > 65535) {
                    System.out.println("Usage: java UDP_Unicast_Server [serverPort>1024]");
                    System.out.println("Errore: 1024<serverPort<65535.");
                    System.exit(1);
                }
                System.out.println("porta: " + port);
            } catch (NumberFormatException e) {
                System.out.println("Usage: java UDP_Unicast_Server [serverPort>1024]");
                System.out.println("serverPort deve essere un'intero");
                System.exit(1);
            }
        } else {
            System.out.println("Usage: java UDP_Unicast_Server [serverPort>1024]");
            System.exit(1);
        }

        // dichiarazione e creazione socket e packet
        DatagramSocket socket = null;
        DatagramPacket packet = null;
        byte[] buf = new byte[256];

        try {
            System.out.println("[UDP_Unicast_Server]: Avvio");
            socket = new DatagramSocket(port);
            packet = new DatagramPacket(buf, buf.length);
            System.out.println("[UDP_Unicast_Server]: Creata socket " + socket);

        } catch (SocketException e) {
            System.out.println("Problemi nella creazione della socket: ");
            e.printStackTrace();
            System.out.println("[UDP_Unicast_Server]: Termino");
            System.exit(1);
        }

        try {
            ByteArrayInputStream biStream = null;
            DataInputStream diStream = null;
            ByteArrayOutputStream boStream = null;
            DataOutputStream doStream = null;
            byte[] data = null;

            // TODO VARIABILI PER LA LOGICA DEL PROGRAMMA
            String richiesta = null;
            String risposta = null;

            while (true) {
                System.out.println("[UDP_Unicast_Server]: In attesa di richieste");

                // ricezione della richiesta
                try {
                    packet.setData(buf);
                    socket.receive(packet);
                } catch (Exception e) {
                    System.out.println("Problemi durante la ricezione del datagramma: ");
                    e.printStackTrace();
                    continue;
                }

                // lettura della richiesta
                try {
                    biStream = new ByteArrayInputStream(packet.getData(), 0, packet.getLength());
                    diStream = new DataInputStream(biStream);
                    // TODO LETTURA RICHIESTA (esempio stringa)
                    richiesta = diStream.readUTF();
                    System.out.println("Ricevuto: " + richiesta);

                } catch (Exception e) {
                    System.out.println("[UDP_Unicast_Server]: Problemi nella lettura della richiesta: ");
                    e.printStackTrace();
                    continue;
                }

                // elaborazione richiesta ed invio risposta
                try {
                    // TODO ELABORAZIONE DELLA RICHIESTA

                    boStream = new ByteArrayOutputStream();
                    doStream = new DataOutputStream(boStream);

                    // TODO INVIO RISPOSTA (esempio stringa)
                    doStream.writeUTF(risposta);

                    data = boStream.toByteArray();
                    packet.setData(data, 0, data.length);
                    socket.send(packet);
                    System.out.println("Inviato: " + risposta);

                } catch (IOException e) {
                    System.out.println("[UDP_Unicast_Server]: Problemi nell'invio della risposta: ");
                    e.printStackTrace();
                    continue;
                }
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println("[UDP_Unicast_Server]: Termino");
        socket.close();
    }
}
