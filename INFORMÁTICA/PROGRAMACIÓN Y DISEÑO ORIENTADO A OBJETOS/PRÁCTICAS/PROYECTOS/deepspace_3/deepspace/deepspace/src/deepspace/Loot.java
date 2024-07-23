/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;

//Esta clase representa el botín que se obtiene al vencer a una nave enemiga
//Puede incluir paquetes de suministros, armas, potenciadores de escudo, 
//hangares y/o medallas.
class Loot {
    
    private int nSupplies;
    private int nWeapons;
    private int nShields;
    private int nHangars;
    private int nMedals;
    
    Loot (int nSupplies, int nWeapons, int nShields, int nHangars, int nMedals){
        
        this.nSupplies = nSupplies;
        this.nWeapons = nWeapons;
        this.nShields = nShields;
        this.nHangars = nHangars;
        this.nMedals = nMedals;
        
    }
    
    LootToUI getUIversion(){
        
        return (new LootToUI(this));
        
    }
    
    
    public int getNSupplies(){
        
        return nSupplies;
        
    }
    
    public int getNWeapons(){
        
        return nWeapons;
        
    }
    
    public int getNShields(){
        
        return nShields;
        
    }
    
    public int getNHangars(){
        
        return nHangars;
        
    }
    
    public int getNMedals(){
        
        return nMedals;
        
    }
    
    
    public String toString(){
        
        String output= "Loot attributes:\n"      +
                       "nSupplies: " + nSupplies + "\n"  +
                       "nWeapons: "  + nWeapons  + "\n" +
                       "nShields: "  + nShields  + "\n" +
                       "nHangars: "  + nHangars  + "\n" +
                       "nMedals: "   + nMedals   + "\n";
        
        return output;
    }
    
}
