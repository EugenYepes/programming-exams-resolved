import java.util.Scanner;

public class Resolucion {
	static Scanner scanner = new Scanner(System.in);
	static final int CANT_CIUDADES = 10;
	static final String COD_DRONE_SALIDA = "FIN";
	static final int MAX_TIEMPO_VUELO = 1440;
	public static void main(String[] args) {		
		int totalEntregasCiudades = 0;
		int maxEntregas = 0;
		String codDroneMaxEntregas = "";
		
		for (int i = 0; i < CANT_CIUDADES; i++) {
			String nombreCiudad;
			do {
				System.out.println("Ingrese el nombre de la ciudad");
				nombreCiudad = scanner.nextLine();
				if (nombreCiudad.isEmpty()) {
					System.out.println("Nombre de la ciudad vacio, vuelva a intentarlo");
				}
			} while (nombreCiudad.isEmpty());
			
			String codDrone;
			int totalVuelo = 0;
			int totalEntregas = 0;
			int cantDrones = 0;

			do {
				System.out.println("Ingrese el codigo del drone para la ciudad (Fin para salir)" + nombreCiudad);
				codDrone = scanner.nextLine();
				if (codDrone.isEmpty()) {
					System.out.println("Codigo del drone vacio, vuelva a intentarlo");
					
				} else if (!codDrone.equalsIgnoreCase(COD_DRONE_SALIDA)) {
					
					int cantEntregas;
					do {
						System.out.println("Ingrese la cantidad de entregas del drone " + codDrone);
						cantEntregas = Integer.parseInt(scanner.nextLine());
						if (cantEntregas < 0) {
							System.out.println("La cantidad de entregas tiene que ser mayor a 0, vuelva a intentarlo");
						}
					} while(cantEntregas < 0);
					
					int tiempoVuelo;
					do {
						System.out.println("Ingrese el tiempo de vuelo del drone " + codDrone);
						tiempoVuelo = Integer.parseInt(scanner.nextLine());
						if (tiempoVuelo < 0 || tiempoVuelo > MAX_TIEMPO_VUELO) {
							System.out.println("El tiempo de vuelo tiene que estar entre 0 y 1440, vuelva a intentarlo");
						}
					} while(tiempoVuelo < 0 || tiempoVuelo > MAX_TIEMPO_VUELO);
					
					// calculo de pedidos de drones de una ciudad
					totalVuelo += tiempoVuelo;
					totalEntregas += cantEntregas;
					cantDrones++;
					
					// calculos totales
					if (cantEntregas > maxEntregas) {
						maxEntregas = cantEntregas;
						codDroneMaxEntregas = codDrone;
					}
				}
			} while(!codDrone.equalsIgnoreCase(COD_DRONE_SALIDA));
			
			if (cantDrones == 0) {
				System.out.println("Sin datos de entregas para " + nombreCiudad);
			} else {
				System.out.println("El tiempo de vuelo total es: " + totalVuelo);
				double promedio = (double)totalEntregas/cantDrones; 
				System.out.println("El promedio de entregas para " + nombreCiudad + " es " + promedio);
			}
			
			// total entregas
			totalEntregasCiudades += totalEntregas;
		}
	
		System.out.println("El total de entregas para todas las ciudades es: " + totalEntregasCiudades);
		System.out.println("El drone que realizo mas entregas es: " + codDroneMaxEntregas + " que realizo " + maxEntregas + " entregas.");
	}
}
