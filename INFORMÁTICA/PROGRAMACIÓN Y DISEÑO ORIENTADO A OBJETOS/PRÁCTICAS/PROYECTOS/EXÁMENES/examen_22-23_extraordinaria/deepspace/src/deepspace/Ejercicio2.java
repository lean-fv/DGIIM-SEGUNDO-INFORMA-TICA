/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package deepspace;
import java.util.ArrayList;

/**
 *
 * @author leandrofdez
 */
public class Ejercicio2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        ArrayList<SpaceFighter> fighters = new ArrayList<>();
        final int NFIGHTERS=2;
        
        CardDealer dealer = CardDealer.getInstance();
        
        
        for (int i=0; i<NFIGHTERS; i++){
            
            fighters.add(new SpaceStation("Estacion",dealer.nextSuppliesPackage()));
            fighters.add(dealer.nextEnemy());
        }
        
        for (int i=0; i<fighters.size();i++)
            
            System.out.println(fighters.get(i).fire());
    }
    
}
