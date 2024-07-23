/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package deepspace;
import java.util.ArrayList;

/**
 *
 * @author leandrofdez
 */
public class ExamenP4 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        final int NSTATIONS=5;
        ArrayList<SpaceStation> stations= new ArrayList<>();
        
        for (int i=0; i<NSTATIONS; i++){
            
            stations.add(new SpaceStation(Integer.toString(i), new SuppliesPackage(1,1,1)));
            
        }
        
        ArrayList<SpaceStation> copia = new ArrayList<SpaceStation>(stations);
        copia.remove(1);
        SpaceCity city = new SpaceCity(stations.get(1),copia);
        
        stations.set(1, city);
        
        for (int i=0; i<stations.size();i++){
            
            System.out.println(stations.get(i).fire());
        }
    }
    
}
