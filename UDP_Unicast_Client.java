// Filippo Serafini
// 0000723678
// UDP_Unicast_Client.java

import java.io.*;
import java.net.*;

public class UDP_Unicast_Client {

    public static void main(String[] args) {

        InetAddress addr = null;
        int port = -1;

        // controllo argomenti
        try {
            if (args.length == 2) {
                addr = InetAddress.getByName(args[0]);
                port = Integer.parseInt(args[1]);
            } else {
                System.out.println("Usage: java UDP_Unicast_Client serverIP serverPort");
                System.exit(1);
            }
        } catch (UnknownHostException e) {
            System.out.println("Problemi durante la determinazione dell'endpoint del server : ");
            e.printStackTrace();
            System.exit(1);
        } catch (NumberFormatException e) {
            System.out.println("Usage: java UDP_Unicast_Client serverIP serverPort");
            System.out.println("serverPort deve essere un intero");
            System.exit(1);
        }

        // dichiarazione e creazione socket e packet
        DatagramSocket socket = null;
        DatagramPacket packet = null;
        byte[] buf = new byte[256];

        try {
            socket = new DatagramSocket();
            socket.setSoTimeout(30000);
            packet = new DatagramPacket(buf, buf.length, addr, port);

        } catch (SocketException e) {
            System.out.println("Problemi durante la creazione della socket: ");
            e.printStackTrace();
            System.exit(1);
        }

        // standard input per l'interazione con l'utente
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("\t----------\nRICHIESTA, EOF per terminare: ");

        try {
            ByteArrayOutputStream boStream = null;
            DataOutputStream doStream = null;
            ByteArrayInputStream biStream = null;
            DataInputStream diStream = null;
            byte[] data = null;

            // TODO VARIABILI PER LA LOGICA DEL PROGRAMMA
            String richiesta = null;
            String esito = null;

            while ((richiesta = stdIn.readLine()) != null) {
                try {
                    // TODO INTERAZIONE CON L'UTENTE


                } catch (Exception e) {
                    System.out.println("Problemi durante l'interazione con l'utente: ");
                    e.printStackTrace();
                    System.out.print("\t----------\nRICHIESTA, EOF per terminare: ");
                    continue;
                }

                // preparazione ed invio della richiesta
                try {
                    boStream = new ByteArrayOutputStream();
                    doStream = new DataOutputStream(boStream);

                    // TODO INVIO RICHIESTA (esempio stringa)
                    doStream.writeUTF(richiesta);
                    data = boStream.toByteArray();
                    packet.setData(data);
                    socket.send(packet);
                    System.out.println("Inviato: " + richiesta);

                } catch (IOException e) {
                    System.out.println("Problemi durante l'invio della richiesta: ");
                    e.printStackTrace();
                    System.out.print("\t----------\nRICHIESTA, EOF per terminare: ");
                    continue;
                }

                // ricezione risposta
                try {
                    packet.setData(buf);
                    socket.receive(packet);

                } catch (IOException e) {
                    System.out.println("Problemi durante la ricezione della risposta: ");
                    e.printStackTrace();
                    System.out.print("\t----------\nRICHIESTA, EOF per terminare: ");
                    continue;
                }

                // elaborazione risposta
                try {
                    biStream = new ByteArrayInputStream(packet.getData(), 0, packet.getLength());
                    diStream = new DataInputStream(biStream);

                    // TODO RICEZIONE ESITO (esempio stringa)
                    esito = diStream.readUTF();
                    System.out.println("Risultato: " + esito);

                } catch (SocketTimeoutException ste) {
                    System.out.println("Timeout scattato: ");
                    ste.printStackTrace();
                    System.out.print("\t----------\nRICHIESTA, EOF per terminare: ");
                    continue;

                } catch (IOException e) {
                    System.out.println("Problemi durante la lettura della risposta: ");
                    e.printStackTrace();
                    System.out.print("\t----------\nRICHIESTA, EOF per terminare: ");
                    continue;
                }
                System.out.print("\t----------\nRICHIESTA, EOF per terminare: ");
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        socket.close();
    }
}
