/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package main;

import View.ExamenP5View;
import View.GUI.ExamenP5;
import controller.ExamenP5Controller;
import deepspace.GameUniverse;

/**
 *
 * @author leandrofdez
 */
public class PlayWithExamenP5 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        GameUniverse game = new GameUniverse();
        ExamenP5View view = ExamenP5.getInstance();
        ExamenP5Controller controller = ExamenP5Controller.getInstance();
        controller.setModelView (game,view);
        controller.start(); 
    }
    
}
