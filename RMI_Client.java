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
            System.out.println("ClientRMI: Service \"" + serviceName + "\" connected");

            // TODO LOGICA CLIENT

        }	catch(Exception e){
            System.err.println("ClientRMI: " + e.getMessage());
            e.printStackTrace();
            System.exit(1);
        }
    }
}
