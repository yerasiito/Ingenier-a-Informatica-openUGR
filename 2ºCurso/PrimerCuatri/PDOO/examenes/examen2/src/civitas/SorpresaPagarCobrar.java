/**
 * @file SorpresaPagarCobrar.java
 * @date Diciembre de 2021
 */
package civitas;

import java.util.ArrayList;

/**
 * @brief Clase Hija de Sorpresa que gestiona la Sorpresa de PAGARCOBRAR
 */
public class SorpresaPagarCobrar extends Sorpresa{

    public SorpresaPagarCobrar(String texto, int valor) {
        super(texto, valor);
    }
    
    @Override
    void aplicarAJugador(int actual, ArrayList<Jugador> todos){
        informe(actual, todos);
        todos.get(actual).modificarSaldo(valor);
    }
    
    @Override
    void informe(int actual, ArrayList<Jugador> todos){
        String evento = "El jugador " + todos.get(actual).getNombre() +
                " se le ha aplicado una Sorpresa de PAGARCOBRAR: " + toString();
        Diario.getInstance().ocurreEvento(evento);
    }
    
    @Override
    public String toString(){
        return super.toString() + " una unica vez";
    }
    
}
