// Filippo Serafini
// 0000723678
// RMI_Server.java

import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class RMI_Server extends UnicastRemoteObject implements RMI_InterfaceFile {
	private static final long serialVersionUID = 1L;

	// costruttore
	public RMI_Server() throws RemoteException	{
		super();
	}

	// implementazione metodi interfaccia
    // TODO

	//main
	public static void main(String[] args) {
		final int REGISTRYPORT = 1099;
		String registryHost = "localhost";
		String serviceName = "RMI_service_name"; //TODO

		// registrazione del servizio RMI
		String completeName = "//" + registryHost + ":" + REGISTRYPORT + "/" + serviceName;
		try{
			RMI_Server serverRMI = new RMI_Server();
			Naming.rebind(completeName, serverRMI);
			System.out.println("RMI service: Service \"" + serviceName + "\" registered");
		}
		catch(Exception e){
			System.err.println("Server RMI \"" + serviceName + "\": " + e.getMessage());
			e.printStackTrace();
			System.exit(1);
		}
	}
}
