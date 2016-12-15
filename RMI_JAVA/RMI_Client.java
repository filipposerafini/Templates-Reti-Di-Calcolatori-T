// Filippo Serafini
// 0000723678
// RMI_Client.java

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.rmi.Naming;


public class RMI_Client {

    // avvio del client RMI
    public static void main(String[] args) {
        final int REGISTRYPORT = 1099;
        String registryHost = null;
        String serviceName = "RMI_service_name"; //TODO
        BufferedReader stdIn = new BufferedReader(new InputStreamReader(System.in));

        // controllo argomenti
        if(args.length != 1){
            System.out.println("Usage: RMI_Client serverAddress");
            System.exit(1);
        }
        registryHost = args[0];

        // connessione al servizio RMI remoto
        try{
            String completeName = "//" + registryHost + ":" + REGISTRYPORT + "/" + serviceName;
            RMI_InterfaceFile serverRMI = (RMI_InterfaceFile) Naming.lookup(completeName);
            System.out.println("[RMI_Client]: Service \"" + serviceName + "\" connected");

            String command;
            System.out.print("\n----------------------------------------\nCMD - FUNZIONE, EOF per terminare: ");
            while ((command = stdIn.readLine()) != null) {
                if (command.equals("CMD")) {

                    // TODO LOGICA CLIENT

                } else 
                    System.out.println("Comando non valido");
                System.out.print("\n----------------------------------------\nCMD - FUNZIONE, EOF per terminare: ");
            }

        }	catch(Exception e){
            e.printStackTrace();
            System.exit(1);
        }
    }
}
