package src_LOPEZ_RAMIREZ_YERAY;

import java.io.IOException;
import java.util.ArrayList;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

public class AgenteAStar extends AbstractPlayer{
	//Atributos de la clase
	private boolean listaCerrados[][]; // Nodos visitados, incluye muros y trampas. false no visitado, true visitado
    private PriorityQueueNodo listaAbiertos = new PriorityQueueNodo(); // Nodos sin visitar
    protected ArrayList<Nodo> HijosActual = new ArrayList<>(); // Hijos en la ejecucion
	private ArrayList<ACTIONS> camino = new ArrayList<ACTIONS>(); // El camino generado hacia la meta
	
    
    private Vector2d portalFin;
    private Vector2d fescala;
    private Vector2d posicionJugador;
  
	/**
	 * initialize all variables for the agent
	 * @param stateObs Observation of the current state.
     * @param elapsedTimer Timer when the action returned is due.
	 * @throws IOException 
	 */
	public AgenteAStar(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		// Calcular la escala de la cuadrícula
		fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length , 
        		stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);      
		
		// Calcular las dimensiones del mundo
		int columnas = (int)(stateObs.getWorldDimension().width/fescala.x);
		int filas = (int)(int)(stateObs.getWorldDimension().height/fescala.y);
      
	    // Encontrar el portal
        ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions(stateObs.getAvatarPosition());
        portalFin = posiciones[0].get(0).position;
        portalFin.x = Math.floor(portalFin.x / fescala.x);
        portalFin.y = Math.floor(portalFin.y / fescala.y);
		
		// Encontrar las posiciones de los obstáculos y agregarlas a la matriz de cerrados
		ArrayList<Observation>[] listadoInnamovible = stateObs.getImmovablePositions(stateObs.getAvatarPosition());
		listaCerrados = new boolean[filas][columnas];
		for(ArrayList<Observation> obsList : listadoInnamovible) {
			for(Observation obs : obsList) {
				int posy = (int)(obs.position.y/fescala.y); //La pos y en la matriz es la fila
				int posx = (int)(obs.position.x/fescala.x); //La pos x en la matriz es la columna
				listaCerrados[posy][posx] = true;
			}
		}
	
		// Obtener la posicion del jugador
		posicionJugador = new Vector2d(stateObs.getAvatarPosition().x/fescala.x, stateObs.getAvatarPosition().y/fescala.y);
	}
	
	int nodosExpandidos = 0;
	private ArrayList<ACTIONS> AlgoritmoAstar(StateObservation mundo){
		boolean estaAbiertos = false, estaCerrados = false;
		Nodo actual;
		Nodo nodoInicial = new Nodo(posicionJugador, null, null, portalFin, true);
		
		listaAbiertos.add(nodoInicial);	
		
		while(!listaAbiertos.isEmpty()) { //Mientras no encuentre el objetivo	
	        // Seleccionar el nodo con la menor distancia a la meta
			actual = listaAbiertos.poll();
			
	        // Añadir la posición del nodo actual a la lista de nodos cerrados
			listaCerrados[(int)actual.getPosicion().y][(int)actual.getPosicion().x] = true;
			
			if(actual.isEstadoFinal()) {
	            // Si se ha alcanzado el estado final, construir el camino de acciones
				camino.add(actual.getAccion());
				while(actual.getPadre() != null) {
					actual = actual.getPadre();
					camino.add(actual.getAccion());
				}
				nodosExpandidos++;
				// Terminar la busqueda
				break;
			}
			
			// Expandir los nodos hijos del nodo actual
			ArrayList<Nodo> hijos = actual.expandirHijos(mundo);
			for(Nodo n : hijos) {
				estaCerrados = listaCerrados[(int)n.getPosicion().y][(int)n.getPosicion().x];
				estaAbiertos = listaAbiertos.contains(n);
				
				// Si el nodo hijo está en cerrados y tiene mejor coste que el actual
				if(estaCerrados && actual.mejorCaminoA(n)) {
					// Lo sacamos de cerrados
					listaCerrados[(int)n.getPosicion().y][(int)n.getPosicion().x] = false;
					
					//Actualiza el nodo con el sucesor quitando el actual y metiendo el mejor
					listaAbiertos.remove(n);
					listaAbiertos.add(n);
				}
				else if(!estaCerrados && !estaAbiertos) { // Si el nodo hijo no está en cerrados ni abiertos lo añadimos a abiertos
					listaAbiertos.add(n);
				}
				else if(estaAbiertos && actual.mejorCaminoA(n)) { // Si el nodo hijo esta en abiertos
					//Actualiza el nodo con el sucesor quitando el actual y metiendo el mejor
					listaAbiertos.remove(n);
					listaAbiertos.add(n);
				}
			}
	        // Incrementar el número de nodos expandidos
			nodosExpandidos++;
		}
		return camino;
	}
	//FIN DEL ALGORITMO
	
	void imprimeInfo(long tInicio) {
		long tFin = System.nanoTime();
		long tiempoTotalms = (tFin - tInicio)/1000000;
		System.out.println("Tiempo de busqueda total: " + tiempoTotalms + " ms");
		System.out.println("Tamaño del camino: " + (camino.size()-1));
		System.out.println("Nodos expandidos: " + nodosExpandidos);
	} 
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {	
	    ACTIONS accion = null;
	    // Calcular el camino con Dijkstra
		if (camino.isEmpty()) {
		    listaAbiertos.clear();
			long tInicio = System.nanoTime(); //Mide el tiempo de busqueda
	    	camino = AlgoritmoAstar(stateObs);
	    	imprimeInfo(tInicio); // Imprime la info estrictamente necesaria
        }
		
	    
	    // Obtener la accion a realizar del camino
		if(!camino.isEmpty())
			accion = camino.remove(camino.size()-1);
			
		return accion; 
	}	
	
}