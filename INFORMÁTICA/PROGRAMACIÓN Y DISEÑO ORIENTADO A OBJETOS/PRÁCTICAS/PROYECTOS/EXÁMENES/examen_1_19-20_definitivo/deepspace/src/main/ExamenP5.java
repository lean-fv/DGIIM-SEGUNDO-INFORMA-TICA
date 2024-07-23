/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package main;

import View.GUI.ExamView;
import controller.ExamController;
import deepspace.GameUniverse;

/**
 *
 * @author leandrofdez
 */
public class ExamenP5 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        GameUniverse game = new GameUniverse();
        ExamView view = ExamView.getInstance();
        ExamController controller = ExamController.getInstance();
        controller.setModelView (game,view);
        controller.start(); 
    }
    
}
